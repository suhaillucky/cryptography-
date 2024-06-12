#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to calculate the greatest common divisor (GCD) of two numbers
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// Function to check if 'a' and 'b' form a valid pair for the affine cipher
int isValidParameters(int a, int b) {
    return gcd(a, ALPHABET_SIZE) == 1; // 'a' and 26 should be coprime
}

// Function to normalize a number to the range [0, ALPHABET_SIZE)
int mod(int a) {
    return (a % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE;
}

// Function to encrypt a single character using the affine cipher
char affineEncrypt(int a, int b, char plainChar) {
    if (!isalpha(plainChar)) {
        return plainChar; // If not an alphabet, return unchanged
    }

    int plainValue = toupper(plainChar) - 'A';
    int cipherValue = mod((a * plainValue + b) % ALPHABET_SIZE);
    return 'A' + cipherValue;
}

// Function to decrypt a single character using the affine cipher
char affineDecrypt(int a, int b, char cipherChar) {
    if (!isalpha(cipherChar)) {
        return cipherChar; // If not an alphabet, return unchanged
    }

    int cipherValue = toupper(cipherChar) - 'A';
    // Find the modular multiplicative inverse of 'a' with respect to ALPHABET_SIZE
    int aInverse;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if ((a * i) % ALPHABET_SIZE == 1) {
            aInverse = i;
            break;
        }
    }
    int plainValue = mod(aInverse * (cipherValue - b));
    return 'A' + plainValue;
}

// Function to print limitations on the values of 'a' and 'b'
void printLimitations() {
    printf("Limitations:\n");
    printf("1. 'a' must be coprime with %d\n", ALPHABET_SIZE);
    printf("2. 'b' can take any value from 0 to %d\n", ALPHABET_SIZE - 1);
}

int main() {
    int a, b;
    
    printf("Enter the value of a: ");
    scanf("%d", &a);
    printf("Enter the value of b: ");
    scanf("%d", &b);

    if (!isValidParameters(a, b)) {
        printf("Invalid parameters. Please choose different values.\n");
        printLimitations();
        return 1;
    }

    char plaintext[] = "AFFINECIPHER";
    char encrypted[strlen(plaintext) + 1];
    char decrypted[strlen(plaintext) + 1];

    printf("Original plaintext: %s\n", plaintext);

    // Encrypt the plaintext
    for (int i = 0; plaintext[i] != '\0'; i++) {
        encrypted[i] = affineEncrypt(a, b, plaintext[i]);
    }
    encrypted[strlen(plaintext)] = '\0';
    printf("Encrypted text: %s\n", encrypted);

    // Decrypt the ciphertext
    for (int i = 0; encrypted[i] != '\0'; i++) {
        decrypted[i] = affineDecrypt(a, b, encrypted[i]);
    }
    decrypted[strlen(plaintext)] = '\0';
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}

