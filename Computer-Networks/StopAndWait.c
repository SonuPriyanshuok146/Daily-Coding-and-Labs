#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TIMEOUT 5
#define MAX_FRAMES 20

struct timer {
    clock_t startTime;
};

void startTimer(struct timer *t) {
    t->startTime = clock();
}

double elapsedTime(struct timer *t) {
    return (double)(clock() - t->startTime) / CLOCKS_PER_SEC;
}

int isTimeout(struct timer *t) {
    return elapsedTime(t) >= TIMEOUT;
}

/* Simulate a delay using CPU time */
void simulateDelay(double seconds) {
    clock_t start = clock();

    while ((double)(clock() - start) / CLOCKS_PER_SEC < seconds) {
        /* Wait */
    }
}

int main(void) {
    int n, frames[MAX_FRAMES];
    int i = 0;
    int expectedFrame = 0;
    int delivered[MAX_FRAMES] = {0};
    int attempt;

    struct timer t;

    srand((unsigned int)time(NULL));

    printf("Enter number of frames: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_FRAMES) {
        printf("Invalid number of frames.\n");
        return 1;
    }

    printf("Enter frames:\n");
    for (int j = 0; j < n; j++) {
        if (scanf("%d", &frames[j]) != 1) {
            printf("Invalid input.\n");
            return 1;
        }
    }

    printf("\nFrames to be sent: ");
    for (int j = 0; j < n; j++)
        printf("%d ", frames[j]);

    printf("\n\nSender\t\t\tReceiver\n");

    while (i < n) {
        int frameReceived = 0;
        int ackReceived = 0;

        printf("\nSending Frame: %d\n", frames[i]);

        startTimer(&t);

        /* Randomly simulate frame loss */
        if (rand() % 4 == 0) {
            simulateDelay(TIMEOUT + 0.1);
        } else {
            simulateDelay(0.1);
            frameReceived = !isTimeout(&t);
        }

        if (!frameReceived) {
            printf("Frame lost or timed out.\n");
            printf("Timeout! Retransmitting Frame: %d\n", frames[i]);
            continue;
        }

        /* Receiver handles a frame only once */
        if (expectedFrame == i && !delivered[i]) {
            printf("Receiver: Frame %d received.\n", frames[i]);
            delivered[i] = 1;
            expectedFrame++;
        } else {
            printf("Receiver: Duplicate frame detected.\n");
        }

        startTimer(&t);

        /* Randomly simulate ACK loss */
        if (rand() % 4 == 0) {
            simulateDelay(TIMEOUT + 0.1);
        } else {
            simulateDelay(0.1);
            ackReceived = !isTimeout(&t);
        }

        if (ackReceived) {
            printf("Sender: ACK received for Frame %d.\n", frames[i]);
            i++;
        } else {
            printf("ACK lost or timed out.\n");
            printf("Sender will retransmit Frame: %d\n", frames[i]);
        }
    }

    printf("\nAll frames delivered successfully.\n");
    return 0;
}