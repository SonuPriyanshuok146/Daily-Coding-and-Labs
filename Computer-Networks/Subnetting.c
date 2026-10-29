
#include <stdio.h>
#include <stdint.h>

int main() {
    unsigned int a, b, c, d;
    int prefix;
    uint32_t ip, mask, network, broadcast;
    unsigned int hosts;

    printf("Enter IP address (a.b.c.d): ");
    scanf("%u.%u.%u.%u", &a, &b, &c, &d);

    if (a > 255 || b > 255 || c > 255 || d > 255) {
        printf("Invalid IP address.\n");
        return 1;
    }

    printf("Enter prefix length (0-32): ");
    scanf("%d", &prefix);

    if (prefix < 0 || prefix > 32) {
        printf("Invalid prefix length.\n");
        return 1;
    }

    ip = ((uint32_t)a << 24) | ((uint32_t)b << 16)
       | ((uint32_t)c << 8) | d;

    mask = (prefix == 0) ? 0 : (0xFFFFFFFFu << (32 - prefix));
    network = ip & mask;
    broadcast = network | ~mask;

    printf("\nNetwork address: %u.%u.%u.%u\n",
           network >> 24, (network >> 16) & 255,
           (network >> 8) & 255, network & 255);

    printf("Subnet mask: %u.%u.%u.%u\n",
           mask >> 24, (mask >> 16) & 255,
           (mask >> 8) & 255, mask & 255);

    printf("Broadcast address: %u.%u.%u.%u\n",
           broadcast >> 24, (broadcast >> 16) & 255,
           (broadcast >> 8) & 255, broadcast & 255);

    if (prefix <= 30) {
        hosts = (1u << (32 - prefix)) - 2;
        printf("Usable hosts: %u\n", hosts);
    } else if (prefix == 31) {
        printf("Usable addresses: 2 (point-to-point link)\n");
    } else {
        printf("Usable addresses: 1\n");
    }

    return 0;
}
