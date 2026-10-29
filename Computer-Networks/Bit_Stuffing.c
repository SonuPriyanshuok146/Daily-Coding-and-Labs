#include<stdio.h>
#include<string.h>
int main(){
    char data[100], stuffed[150];
    printf("Enter the Binary data: ");
    scanf("%s",data);


    int j = 0;
    int count = 0;
    for(int i = 0; i < strlen(data); i++){
        stuffed[j++] = data[i];


        if(data[i] == '1'){
            count++;
            if(count == 5){
                stuffed[j++] = '0';
                count = 0;
            }
        }else{
            count = 0;
        }
    }
    stuffed[j] = '\0';
    printf("Original Data: %s\n",data);
    printf("Stuffed Data: %s\n",stuffed);
    return 0;
}
