#include<stdio.h>
#include<string.h>


int main(){
    char data[100], stuffed[200];
    printf("Enter the data: ");
    scanf("%s",data);


    int j = 0;
    for(int i = 0; i < strlen(data); i++){
        if(data[i] == 'E' || data[i] == 'F'){
            stuffed[j++] = 'E';
        }
        stuffed[j++] = data[i];
    }
    stuffed[j] = '\0';


    printf("Original Data: %s\n",data);
    printf("Stuffed Data: %s\n",stuffed);
    return 0;
}