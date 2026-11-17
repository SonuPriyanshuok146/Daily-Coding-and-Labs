import java.io.IOException;
import java.util.Arrays;
import java.util.Locale;
import java.util.TreeMap;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class MinHash {

  // i-th hash function is  h_i(x) = (a_i * x + b_i) mod N
  //   a_i = i + 1,  b_i = 2i + 1
  static int hash(int i, int x, int N) {
    int a = i + 1;
    int b = 2 * i + 1;
    return (a * x + b) % N;
  }

  // ---------- Job 1: build the signature matrix ----------
  // input line:  row,bit_C1,bit_C2,...      e.g.  1,1,0,1,0
  public static class SignatureMapper
       extends Mapper<LongWritable, Text, Text, Text> {

    public void map(LongWritable key, Text value, Context context)
        throws IOException, InterruptedException {
      String line = value.toString().trim();
      if (line.isEmpty()) return;

      Configuration conf = context.getConfiguration();
      int n = Integer.parseInt(conf.get("numHash"));
      int N = Integer.parseInt(conf.get("N"));

      String[] t = line.split(",");
      int row = Integer.parseInt(t[0].trim());

      for (int c = 1; c < t.length; c++) {
        if (t[c].trim().equals("1")) {   // shingle in column c
          for (int i = 0; i < n; i++) {
            context.write(new Text("C" + c),
                          new Text(i + "," + hash(i, row, N)));
          }
        }
      }
    }
  }

  public static class SignatureReducer
       extends Reducer<Text, Text, Text, Text> {

    public void reduce(Text key, Iterable<Text> values, Context context)
        throws IOException, InterruptedException {
      int n = Integer.parseInt(context.getConfiguration().get("numHash"));
      int[] min = new int[n];
      Arrays.fill(min, Integer.MAX_VALUE);

      for (Text v : values) {
        String[] t = v.toString().split(",");
        int i = Integer.parseInt(t[0]);
        int h = Integer.parseInt(t[1]);
        if (h < min[i]) min[i] = h;      // keep the minimum
      }

      StringBuilder sb = new StringBuilder();
      for (int i = 0; i < n; i++) {
        if (i > 0) sb.append(",");
        sb.append(min[i]);
      }
      context.write(key, new Text(sb.toString()));
    }
  }

  // ---------- Job 2: show matrix and estimate similarities ----------
  public static class SimilarityMapper
       extends Mapper<LongWritable, Text, Text, Text> {

    public void map(LongWritable key, Text value, Context context)
        throws IOException, InterruptedException {
      String line = value.toString().trim();
      if (line.isEmpty()) return;
      context.write(new Text("ALL"), new Text(line));   // single reducer
    }
  }

  public static class SimilarityReducer
       extends Reducer<Text, Text, Text, Text> {

    public void reduce(Text key, Iterable<Text> values, Context context)
        throws IOException, InterruptedException {
      TreeMap<Integer, int[]> cols = new TreeMap<Integer, int[]>();
      int n = 0;

      for (Text v : values) {
        String[] p = v.toString().split("\t");
        int col = Integer.parseInt(p[0].substring(1));
        String[] s = p[1].split(",");
        int[] sig = new int[s.length];
        for (int i = 0; i < s.length; i++) sig[i] = Integer.parseInt(s[i]);
        cols.put(col, sig);
        n = s.length;
      }

      Integer[] ids = cols.keySet().toArray(new Integer[0]);

      // signature matrix, one line per hash function
      for (int i = 0; i < n; i++) {
        StringBuilder sb = new StringBuilder();
        for (int c = 0; c < ids.length; c++) {
          if (c > 0) sb.append(" ");
          sb.append(cols.get(ids[c])[i]);
        }
        context.write(new Text("H" + (i + 1)), new Text(sb.toString()));
      }

      // similarity = fraction of hash functions on which two columns agree
      for (int a = 0; a < ids.length; a++) {
        for (int b = a + 1; b < ids.length; b++) {
          int same = 0;
          for (int i = 0; i < n; i++) {
            if (cols.get(ids[a])[i] == cols.get(ids[b])[i]) same++;
          }
          double sim = (double) same / n;
          context.write(new Text("C" + ids[a] + ",C" + ids[b]),
              new Text(String.format(Locale.US, "%d/%d\t%.3f", same, n, sim)));
        }
      }
    }
  }

  public static void main(String[] args) throws Exception {
    // args: <input> <output> <numHash> <N>
    Configuration conf = new Configuration();
    conf.set("numHash", args.length > 2 ? args[2] : "3");  // #hash functions
    conf.set("N", args.length > 3 ? args[3] : "7");        // rows (prime)

    Job job1 = Job.getInstance(conf, "minhash signature");
    job1.setJarByClass(MinHash.class);
    job1.setMapperClass(SignatureMapper.class);
    job1.setReducerClass(SignatureReducer.class);
    job1.setOutputKeyClass(Text.class);
    job1.setOutputValueClass(Text.class);
    FileInputFormat.addInputPath(job1, new Path(args[0]));
    FileOutputFormat.setOutputPath(job1, new Path(args[1] + "/signature"));
    if (!job1.waitForCompletion(true)) System.exit(1);

    Job job2 = Job.getInstance(conf, "minhash similarity");
    job2.setJarByClass(MinHash.class);
    job2.setMapperClass(SimilarityMapper.class);
    job2.setReducerClass(SimilarityReducer.class);
    job2.setOutputKeyClass(Text.class);
    job2.setOutputValueClass(Text.class);
    FileInputFormat.addInputPath(job2, new Path(args[1] + "/signature"));
    FileOutputFormat.setOutputPath(job2, new Path(args[1] + "/result"));
    System.exit(job2.waitForCompletion(true) ? 0 : 1);
  }
}
