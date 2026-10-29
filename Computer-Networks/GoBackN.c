#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 50

int main() {
    int n, windowSize;
    int base = 0, nextFrame = 0;
    int frames[MAX];

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
        /* Send frames within the window */
        while (nextFrame < base + windowSize && nextFrame < n) {
            printf("Sending Frame: %d\t", frames[nextFrame]);

            /* Simulate frame loss */
            if (rand() % 5 == 0) {
                printf("Frame lost!\n");
                break;
            } else {
                printf("Frame received: %d\n", frames[nextFrame]);
                nextFrame++;
            }
        }

        if (nextFrame == n) {
            printf("ACK received for Frame: %d\n", frames[n - 1]);
            base = n;
            break;
        }

        if (nextFrame < n && nextFrame < base + windowSize) {
            printf("Timeout! Go back to Frame: %d\n", frames[nextFrame]);

            /* Retransmit from the missing frame */
            nextFrame = base;

            /* In a real protocol, cumulative ACKs determine base.
               This simulation retries the current window. */
            base = nextFrame;
        } else {
            printf("Cumulative ACK received up to Frame: %d\n",
                   frames[nextFrame - 1]);
            base = nextFrame;
        }
    }

    printf("\nAll frames transmitted successfully.\n");
    return 0;
}