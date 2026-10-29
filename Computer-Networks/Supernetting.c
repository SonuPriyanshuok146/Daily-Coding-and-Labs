
#include <stdio.h>
#include <stdint.h>

uint32_t readIP(void) {
    unsigned int a, b, c, d;

    if (scanf("%u.%u.%u.%u", &a, &b, &c, &d) != 4 ||
        a > 255 || b > 255 || c > 255 || d > 255) {
        return 0;
    }

    return ((uint32_t)a << 24) | ((uint32_t)b << 16)
         | ((uint32_t)c << 8) | d;
}

void printIP(uint32_t ip) {
    printf("%u.%u.%u.%u",
           (ip >> 24) & 255, (ip >> 16) & 255,
           (ip >> 8) & 255, ip & 255);
}

int main(void) {
    uint32_t ip1, ip2, mask, network1, network2;
    int p1, p2, prefix;

    printf("Enter first network IP and prefix (e.g. 192.168.0.0 24): ");
    ip1 = readIP();
    if (scanf("%d", &p1) != 1 || p1 < 0 || p1 > 32) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter second network IP and prefix: ");
    ip2 = readIP();
    if (scanf("%d", &p2) != 1 || p2 < 0 || p2 > 32) {
        printf("Invalid input.\n");
        return 1;
    }

    if (p1 != p2 || p1 == 0) {
        printf("Networks must have the same prefix length (1-32).\n");
        return 1;
    }

    mask = 0xFFFFFFFFu << (32 - p1);
    network1 = ip1 & mask;
    network2 = ip2 & mask;

    if (network1 == network2) {
        printf("Both addresses belong to the same network.\n");
        return 0;
    }

    /* Find the common leading bits */
    prefix = 0;
    for (int bit = 31; bit >= 0; bit--) {
        if (((network1 >> bit) & 1u) ==
            ((network2 >> bit) & 1u))
            prefix++;
        else
            break;
    }

    mask = (prefix == 0) ? 0 : (0xFFFFFFFFu << (32 - prefix));

    printf("\nSupernet address: ");
    printIP(network1 & mask);
    printf("/%d\n", prefix);

    printf("Supernet mask: ");
    printIP(mask);
    printf("\n");

    if (prefix >= p1) {
        printf("The two networks are not a single aligned "
               "supernet of the requested size.\n");
    }

    return 0;
}
