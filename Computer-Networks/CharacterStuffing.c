#include <stdio.h>
#include <string.h>

int main() {
    char data[100], stuffed[200];
    int i, j = 0;

    printf("Enter the data: ");
    scanf("%s", data);

    stuffed[j++] = 'D';
    stuffed[j++] = 'L';
    stuffed[j++] = 'E';
    stuffed[j++] = 'S';
    stuffed[j++] = 'T';
    stuffed[j++] = 'X';

    for (i = 0; i < strlen(data); i++) {
        if (data[i] == 'D' && data[i+1] == 'L' &&
            data[i+2] == 'E') {

            stuffed[j++] = 'D';
            stuffed[j++] = 'L';
            stuffed[j++] = 'E';
        }

        stuffed[j++] = data[i];
    }

    stuffed[j++] = 'D';
    stuffed[j++] = 'L';
    stuffed[j++] = 'E';
    stuffed[j++] = 'E';
    stuffed[j++] = 'T';
    stuffed[j++] = 'X';

    stuffed[j] = '\0';

    printf("\nStuffed Data: %s\n", stuffed);

    return 0;
}

// Enter the data: ABCDLEXYZ

// Stuffed Data: DLESTXABCDLEDLEXYZDLEETX