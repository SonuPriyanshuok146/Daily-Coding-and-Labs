import java.io.IOException;
import java.util.HashSet;
import java.util.Locale;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class ShingleJaccard {

  // ---------- Job 1: build the shingle / characteristic matrix ----------
  public static class MatrixMapper
       extends Mapper<LongWritable, Text, Text, Text> {

    public void map(LongWritable key, Text value, Context context)
        throws IOException, InterruptedException {
      String line = value.toString().trim();
      // only lines of the form  S1= {a,d,f}  are sets
      if (!line.matches("^S\\d+\\s*=.*\\{.*\\}.*")) return;

      int k = Integer.parseInt(context.getConfiguration().get("k"));
      String name = line.substring(0, line.indexOf('=')).trim();
      String body = line.substring(line.indexOf('{') + 1, line.indexOf('}'));

      // join the elements of the set and cut it into shingles of length k
      StringBuilder sb = new StringBuilder();
      for (String e : body.split(",")) sb.append(e.trim());
      String text = sb.toString();

      for (int i = 0; i + k <= text.length(); i++) {
        context.write(new Text(text.substring(i, i + k)), new Text(name));
      }
    }
  }

  public static class MatrixReducer
       extends Reducer<Text, Text, Text, Text> {

    public void reduce(Text key, Iterable<Text> values, Context context)
        throws IOException, InterruptedException {
      HashSet<String> present = new HashSet<String>();
      for (Text v : values) present.add(v.toString());

      String[] sets = context.getConfiguration().get("sets").split(",");
      StringBuilder row = new StringBuilder();
      for (int i = 0; i < sets.length; i++) {
        if (i > 0) row.append(",");
        row.append(present.contains(sets[i]) ? "1" : "0");
      }
      context.write(key, new Text(row.toString()));
    }
  }

  // ---------- Job 2: Jaccard similarity and distance ----------
  public static class JaccardMapper
       extends Mapper<LongWritable, Text, Text, Text> {

    public void map(LongWritable key, Text value, Context context)
        throws IOException, InterruptedException {
      String[] parts = value.toString().split("\t");
      if (parts.length < 2) return;
      String[] bits = parts[1].trim().split(",");
      String[] sets = context.getConfiguration().get("sets").split(",");

      for (int i = 0; i < bits.length; i++) {
        for (int j = i + 1; j < bits.length; j++) {
          boolean a = bits[i].equals("1");
          boolean b = bits[j].equals("1");
          if (a && b) {
            context.write(new Text(sets[i] + "," + sets[j]), new Text("1,1"));
          } else if (a || b) {
            context.write(new Text(sets[i] + "," + sets[j]), new Text("0,1"));
          }
        }
      }
    }
  }

  public static class JaccardReducer
       extends Reducer<Text, Text, Text, Text> {

    public void reduce(Text key, Iterable<Text> values, Context context)
        throws IOException, InterruptedException {
      int inter = 0, union = 0;
      for (Text v : values) {
        String[] t = v.toString().split(",");
        inter += Integer.parseInt(t[0]);
        union += Integer.parseInt(t[1]);
      }
      double sim = (double) inter / union;
      String out = String.format(Locale.US, "%d\t%d\t%.3f\t%.3f",
                                 inter, union, sim, 1 - sim);
      context.write(key, new Text(out));
    }
  }

  public static void main(String[] args) throws Exception {
    // args: <input> <output> <k>
    Configuration conf = new Configuration();
    conf.set("k", args.length > 2 ? args[2] : "1");   // shingle length
    conf.set("sets", "S1,S2,S3,S4,S5");

    Job job1 = Job.getInstance(conf, "shingle matrix");
    job1.setJarByClass(ShingleJaccard.class);
    job1.setMapperClass(MatrixMapper.class);
    job1.setReducerClass(MatrixReducer.class);
    job1.setOutputKeyClass(Text.class);
    job1.setOutputValueClass(Text.class);
    FileInputFormat.addInputPath(job1, new Path(args[0]));
    FileOutputFormat.setOutputPath(job1, new Path(args[1] + "/matrix"));
    if (!job1.waitForCompletion(true)) System.exit(1);

    Job job2 = Job.getInstance(conf, "jaccard similarity");
    job2.setJarByClass(ShingleJaccard.class);
    job2.setMapperClass(JaccardMapper.class);
    job2.setReducerClass(JaccardReducer.class);
    job2.setOutputKeyClass(Text.class);
    job2.setOutputValueClass(Text.class);
    FileInputFormat.addInputPath(job2, new Path(args[1] + "/matrix"));
    FileOutputFormat.setOutputPath(job2, new Path(args[1] + "/jaccard"));
    System.exit(job2.waitForCompletion(true) ? 0 : 1);
  }
}
