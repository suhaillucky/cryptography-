#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// Function to remove spaces and duplicate characters from a keyword
void removeSpacesAndDuplicates(char *keyword) {
    int len = strlen(keyword);
    int index = 0;

    // Remove spaces
    for (int i = 0; i < len; i++) {
        if (keyword[i] != ' ') {
            keyword[index++] = toupper(keyword[i]);
        }
    }
    keyword[index] = '\0';

    // Remove duplicate characters
    int seen[26] = {0};
    index = 0;
    for (int i = 0; i < len; i++) {
        if (!seen[keyword[i] - 'A']) {
            seen[keyword[i] - 'A'] = 1;
            keyword[index++] = keyword[i];
        }
    }
    keyword[index] = '\0';
}

// Function to generate the Playfair cipher matrix
void generatePlayfairMatrix(char matrix[SIZE][SIZE], const char *keyword) {
    char alphabet[26] = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // No 'J' in the Playfair matrix
    int keywordLen = strlen(keyword);
    int index = 0;

    // Fill the matrix with the keyword
    for (int i = 0; i < keywordLen; i++) {
        int row = index / SIZE;
        int col = index % SIZE;
        matrix[row][col] = keyword[i];
        index++;

        // Mark letter as used in the alphabet
        alphabet[keyword[i] - 'A'] = '*';
    }

    // Fill the matrix with the remaining letters of the alphabet
    for (int i = 0; i < 26; i++) {
        if (alphabet[i] != '*') {
            int row = index / SIZE;
            int col = index % SIZE;
            matrix[row][col] = alphabet[i];
            index++;
        }
    }
}

// Function to find the row and column of a character in the Playfair matrix
void findRowColumn(char matrix[SIZE][SIZE], char ch, int *row, int *col) {
    if (ch == 'J') // Replace 'J' with 'I'
        ch = 'I';

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt the plaintext using Playfair algorithm
void playfairEncrypt(char matrix[SIZE][SIZE], char *plaintext) {
    int len = strlen(plaintext);
    char encrypted[len * 2 + 1]; // Double the length for two-letter pairs plus one for '\0'
    int index = 0;

    for (int i = 0; i < len; i += 2) {
        char first = plaintext[i];
        char second = (i + 1 < len) ? plaintext[i + 1] : 'X'; // If odd length, append 'X' to the last character

        int row1, col1, row2, col2;
        findRowColumn(matrix, first, &row1, &col1);
        findRowColumn(matrix, second, &row2, &col2);

        if (row1 == row2) { // Same row
            encrypted[index++] = matrix[row1][(col1 + 1) % SIZE];
            encrypted[index++] = matrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) { // Same column
            encrypted[index++] = matrix[(row1 + 1) % SIZE][col1];
            encrypted[index++] = matrix[(row2 + 1) % SIZE][col2];
        } else { // Form a rectangle
            encrypted[index++] = matrix[row1][col2];
            encrypted[index++] = matrix[row2][col1];
        }
    }
    encrypted[index] = '\0';

    printf("Encrypted text: %s\n", encrypted);
}

int main() {
    char keyword[100];
    char plaintext[100];
    char matrix[SIZE][SIZE];

    // Taking keyword input
    printf("Enter the keyword (no spaces, maximum 25 characters): ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';
    removeSpacesAndDuplicates(keyword);

    // Generating the Playfair matrix
    generatePlayfairMatrix(matrix, keyword);

    // Taking plaintext input
    printf("Enter the plaintext (only uppercase letters, no spaces): ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';
    for (int i = 0; plaintext[i] != '\0'; i++) {
        plaintext[i] = toupper(plaintext[i]);
    }

    // Encrypting the plaintext
    playfairEncrypt(matrix, plaintext);

    return 0;
}


