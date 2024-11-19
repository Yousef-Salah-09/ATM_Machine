#define _CRT_SECURE_NO_WARNINGS
#include "util.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Initializing the 2*2 matrix used as a key for hill cipher encryption */
int hillMatrix[2][2] = {
    {6, 24},
    {1, 13}
};

int inverseMatrix[2][2];

/* Function to encrypt a single pin */
void encryptPin(char* pin, char* encryptedPin) {
    int Integer[4];
    Integer[0] = pin[0] - '0';  // Convert first digit to integer
    Integer[1] = pin[1] - '0';  // Convert second digit to integer
    Integer[2] = pin[2] - '0';  // Convert third digit to integer
    Integer[3] = pin[3] - '0';  // Convert fourth digit to integer

    int encryptedInteger[4];

    encryptedInteger[0] = (hillMatrix[0][0] * Integer[0] + hillMatrix[0][1] * Integer[1]) % 10;
    encryptedInteger[1] = (hillMatrix[1][0] * Integer[0] + hillMatrix[1][1] * Integer[1]) % 10;

    encryptedInteger[2] = (hillMatrix[0][0] * Integer[2] + hillMatrix[0][1] * Integer[3]) % 10;
    encryptedInteger[3] = (hillMatrix[1][0] * Integer[2] + hillMatrix[1][1] * Integer[3]) % 10;

    // Combine the encrypted integers into one 4-digit encrypted PIN
    encryptedPin[0] = encryptedInteger[0] + '0';
    encryptedPin[1] = encryptedInteger[1] + '0';
    encryptedPin[2] = encryptedInteger[2] + '0';
    encryptedPin[3] = encryptedInteger[3] + '0';
    encryptedPin[4] = '\0';  // Null terminate
}

/* Function to encrypt all the users passwords */
void encryptPasswords(UserNode* head) {
    UserNode* temp = head;
    while (temp != NULL) {
        char encryptedPin[5];  // Encrypted 4-digit PIN + null terminator
        encryptPin(temp->password, encryptedPin);
        strncpy(temp->password, encryptedPin, 5); // Replace with encrypted PIN
        temp = temp->next;
    }
}


// Function to calculate modular inverse of a number modulo 10
int mod10Inverse(int a) {
    for (int x = 1; x < 10; x++) {
        if ((a * x) % 10 == 1) {
            return x;
        }
    }
    return -1;  // No modular inverse
}


// Function to find the inverse of the Hill cipher matrix modulo 10
void calculateInverseMatrix() {
    int det = (hillMatrix[0][0] * hillMatrix[1][1] - hillMatrix[0][1] * hillMatrix[1][0]) % 10;
    int detInverse = mod10Inverse(det);  // Get the modular inverse of the determinant

    if (detInverse == -1) {
        printf("Matrix is not invertible modulo 10!\n");
        return;
    }
    // Calculate the inverse matrix elements
    inverseMatrix[0][0] = (hillMatrix[1][1] * detInverse) % 10;
    inverseMatrix[0][1] = (-hillMatrix[0][1] * detInverse) % 10;
    inverseMatrix[1][0] = (-hillMatrix[1][0] * detInverse) % 10;
    inverseMatrix[1][1] = (hillMatrix[0][0] * detInverse) % 10;

    // Ensure positive results modulo 10
    inverseMatrix[0][0] = (inverseMatrix[0][0] + 10) % 10;
    inverseMatrix[0][1] = (inverseMatrix[0][1] + 10) % 10;
    inverseMatrix[1][0] = (inverseMatrix[1][0] + 10) % 10;
    inverseMatrix[1][1] = (inverseMatrix[1][1] + 10) % 10;
}

/* Function to decrypt a single pin */
void decryptPin(char* encryptedPin, char* decryptedPin) {
    int Integer[4];
    Integer[0] = encryptedPin[0] - '0';  // Convert first digit to integer
    Integer[1] = encryptedPin[1] - '0';  // Convert second digit to integer
    Integer[2] = encryptedPin[2] - '0';  // Convert third digit to integer
    Integer[3] = encryptedPin[3] - '0';  // Convert fourth digit to integer

    int decryptedInteger[4];

    decryptedInteger[0] = (inverseMatrix[0][0] * Integer[0] + inverseMatrix[0][1] * Integer[1]) % 10;
    decryptedInteger[1] = (inverseMatrix[1][0] * Integer[0] + inverseMatrix[1][1] * Integer[1]) % 10;


    decryptedInteger[0] = (inverseMatrix[0][0] * Integer[2] + inverseMatrix[0][1] * Integer[3]) % 10;
    decryptedInteger[1] = (inverseMatrix[1][0] * Integer[2] + inverseMatrix[1][1] * Integer[3]) % 10;

    // Combine the decrypted integers into one 4-digit decrypted PIN
    decryptedPin[0] = decryptedInteger[0] + '0';
    decryptedPin[1] = decryptedInteger[1] + '0';
    decryptedPin[2] = decryptedInteger[2] + '0';
    decryptedPin[3] = decryptedInteger[3] + '0';
    decryptedPin[4] = '\0';  // Null terminate
}

/* Function to decrypt the password for a specific user by taking the username as an input */
char* decryptUserPasswordByUsername(UserNode* head, const char* username) {
    UserNode* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0) {
            static char decryptedPin[5];  // Use static to return a pointer to the decrypted password
            decryptPin(temp->password, decryptedPin);
            return decryptedPin;
        }
        temp = temp->next;
    }
    return NULL;  // User not found
}