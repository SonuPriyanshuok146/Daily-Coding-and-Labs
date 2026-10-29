#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 50

int main() {
    int n, windowSize;
    int frames[MAX], ack[MAX] = {0};
    int base = 0;

    srand((unsigned int)time(NULL));

    printf("Enter number of frames: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid number of frames.\n");
        return 1;
    }

    printf("Enter frames:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &frames[i]);

    printf("Enter window size: ");
    scanf("%d", &windowSize);

    if (windowSize < 1 || windowSize > n) {
        printf("Invalid window size.\n");
        return 1;
    }

    printf("\nFrames to be sent: ");
    for (int i = 0; i < n; i++)
        printf("%d ", frames[i]);

    printf("\n\nSender\t\t\tReceiver\n");

    while (base < n) {
        int end = base + windowSize;
        if (end > n)
            end = n;

        /* Send each unacknowledged frame in the window */
        for (int i = base; i < end; i++) {
            if (ack[i])
                continue;

            printf("Sending Frame: %d\t", frames[i]);

            /* Simulate frame loss */
            if (rand() % 4 == 0) {
                printf("Frame lost!\n");
                continue;
            }

            printf("Frame received: %d\n", frames[i]);

            /* Simulate ACK loss */
            if (rand() % 4 == 0) {
                printf("ACK lost for Frame: %d\n", frames[i]);
            } else {
                ack[i] = 1;
                printf("ACK received for Frame: %d\n", frames[i]);
            }
        }

        /* Advance window over consecutively acknowledged frames */
        while (base < n && ack[base])
            base++;

        /* Retransmit only frames that remain unacknowledged */
        if (base < n) {
            printf("\nTimeout! Retransmitting unacknowledged frames only.\n");
        }
    }

    printf("\nAll frames transmitted successfully.\n");
    return 0;
}