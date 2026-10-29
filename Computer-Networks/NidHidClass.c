#include <stdio.h>

int main() {
    int a, b, c, d;
    int nid[4], hid[4];

    printf("Enter IPv4 address (four octets): ");
    scanf("%d.%d.%d.%d", &a, &b, &c, &d);

    if (a < 0 || a > 255 || b < 0 || b > 255 ||
        c < 0 || c > 255 || d < 0 || d > 255) {
        printf("Invalid IP address.\n");
        return 1;
    }

    printf("\nIP Address: %d.%d.%d.%d\n", a, b, c, d);

    if (a >= 1 && a <= 126) {
        printf("Class: A\n");
        nid[0] = a;
        hid[0] = 0;
        printf("NID: %d\n", a);
        printf("HID: %d.%d.%d\n", b, c, d);
    }
    else if (a >= 128 && a <= 191) {
        printf("Class: B\n");
        printf("NID: %d.%d\n", a, b);
        printf("HID: %d.%d\n", c, d);
    }
    else if (a >= 192 && a <= 223) {
        printf("Class: C\n");
        printf("NID: %d.%d.%d\n", a, b, c);
        printf("HID: %d\n", d);
    }
    else if (a >= 224 && a <= 239) {
        printf("Class: D (Multicast)\n");
        printf("NID/HID: Not applicable\n");
    }
    else if (a >= 240 && a <= 255) {
        printf("Class: E (Experimental)\n");
        printf("NID/HID: Not applicable\n");
    }
    else {
        printf("Reserved or invalid first octet.\n");
    }

    return 0;
}
