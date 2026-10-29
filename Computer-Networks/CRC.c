#include <stdio.h>
#include <string.h>

int main() {
    char data[100], divisor[30], temp[130];
    int dataLen, divisorLen;

    printf("Enter the data bits: ");
    scanf("%s", data);

    printf("Enter the generator bits: ");
    scanf("%s", divisor);

    dataLen = strlen(data);
    divisorLen = strlen(divisor);

    // Append zeros to the data
    strcpy(temp, data);
    for (int i = 0; i < divisorLen - 1; i++) {
        temp[dataLen + i] = '0';
    }
    temp[dataLen + divisorLen - 1] = '\0';

    // Perform modulo-2 division using XOR
    for (int i = 0; i < dataLen; i++) {
        if (temp[i] == '1') {
            for (int j = 0; j < divisorLen; j++) {
                temp[i + j] =
                    (temp[i + j] == divisor[j]) ? '0' : '1';
            }
        }
    }

    // Construct the transmitted codeword
    printf("CRC remainder: ");
    for (int i = dataLen; i < dataLen + divisorLen - 1; i++) {
        printf("%c", temp[i]);
    }

    printf("\nTransmitted codeword: %s", data);
    for (int i = dataLen; i < dataLen + divisorLen - 1; i++) {
        printf("%c", temp[i]);
    }

    printf("\n");
    return 0;
}