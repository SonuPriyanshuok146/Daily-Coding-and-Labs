#include <stdio.h>
#include <stdint.h>

// Function to calculate the greatest common divisor (GCD)
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find the modular multiplicative inverse using Extended Euclidean Algorithm
long long modInverse(long long e, long long phi) {
    long long t = 0, newt = 1;
    long long r = phi, newr = e;
    
    while (newr != 0) {
        long long quotient = r / newr;
        
        long long temp_t = t;
        t = newt;
        newt = temp_t - quotient * newt;
        
        long long temp_r = r;
        r = newr;
        newr = temp_r - quotient * newr;
    }
    
    if (r > 1) return -1; // e is not invertible
    if (t < 0) t = t + phi;
    
    return t;
}

// Function to calculate (base^exp) % mod using standard long long multiplication
long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

int main() {
    printf("--- RSA Public-Key Cryptographic Algorithm ---\n\n");

    // 1. Key Generation Phase
    long long p = 61;
    long long q = 53;

    // Compute n = p * q
    long long n = p * q;

    // Compute Euler's totient function phi(n) = (p - 1) * (q - 1)
    long long phi = (p - 1) * (q - 1);

    // Choose an integer e such that 1 < e < phi and gcd(e, phi) = 1
    long long e = 17;
    while (e < phi) {
        if (gcd(e, phi) == 1)
            break;
        e++;
    }

    // Compute private key d, the modular multiplicative inverse of e modulo phi
    long long d = modInverse(e, phi);

    printf("Prime numbers (p, q) : %lld, %lld\n", p, q);
    printf("Modulus (n = p * q)    : %lld\n", n);
    printf("Totient phi(n)       : %lld\n", phi);
    printf("Public Key (e, n)    : (%lld, %lld)\n", e, n);
    printf("Private Key (d, n)   : (%lld, %lld)\n\n", d, n);

    // 2. Encryption Phase
    long long plaintext = 65; // Example integer representing message (e.g., ASCII 'A')
    
    if (plaintext >= n) {
        printf("Error: Plaintext must be smaller than modulus n!\n");
        return 1;
    }

    long long ciphertext = power(plaintext, e, n);

    printf("Original Message (M) : %lld\n", plaintext);
    printf("Encrypted Cipher (C) : %lld\n\n", ciphertext);

    // 3. Decryption Phase
    long long decryptedtext = power(ciphertext, d, n);

    printf("Decrypted Message (M): %lld\n", decryptedtext);

    if (plaintext == decryptedtext) {
        printf("\nStatus: Success! Decrypted message matches original plaintext.\n");
    } else {
        printf("\nStatus: Error! Decryption failed.\n");
    }

    return 0;
}