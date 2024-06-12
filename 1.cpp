#include <stdio.h>
#include <ctype.h>

// Function to encrypt the string using Caesar Cipher
void caesarCipher(char *text, int shift) {
    char ch;
    for (int i = 0; text[i] != '\0'; ++i) {
        ch = text[i];
        
        // Encrypt uppercase letters
        if (isupper(ch)) {
            ch = ((ch - 'A' + shift) % 26) + 'A';
        } 
        // Encrypt lowercase letters
        else if (islower(ch)) {
            ch = ((ch - 'a' + shift) % 26) + 'a';
        }
        text[i] = ch;
    }
}

int main() {
    char text[100];
    int shift;

    // Taking string input
    printf("Enter a string: ");
    fgets(text, sizeof(text), stdin);
    
    // Taking shift value input
    printf("Enter shift value (1-25): ");
    scanf("%d", &shift);

    // Ensuring the shift value is within the valid range
    if (shift < 1 || shift > 25) {
        printf("Invalid shift value. Please enter a value between 1 and 25.\n");
        return 1;
    }

    // Encrypting the text
    caesarCipher(text, shift);

    // Output the encrypted text
    printf("Encrypted text: %s\n", text);

    return 0;
}

