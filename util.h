#pragma once
#include <stdlib.h>
#include "User.h"

/* Functions prototypes */
void encryptPasswords(UserNode* head);
void encryptPin(char* pin, char* encryptedPin);
int mod10Inverse(int a);
void calculateInverseMatrix();
void decryptPin(char* encryptedPin, char* decryptedPin);
char* decryptUserPasswordByUsername(UserNode* head, const char* username);