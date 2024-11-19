#define _CRT_SECURE_NO_WARNINGS
#include "User.h"
#include <stdio.h>
#include <string.h>

/* Function to create a user node by taking the user's data as an input */
UserNode* create_user(int user_id, const char* username, const char* password, float current_balance)
{
    UserNode* new_user = (UserNode*)malloc(sizeof(UserNode));
    if (new_user == 0) {
        printf("Memory allocation failed.\n");
        return 0;
    }

    new_user->user_id = user_id;
    strcpy(new_user->username, username);
    strcpy(new_user->password, password);
    new_user->current_balance = current_balance;
    new_user->next = NULL;

    return new_user;
}

/* Function to load the users data from csv file to the linked lists */
void load_user_data_from_CSV(const char* filename, UserNode** head)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return;
    }
    int user_id;
    char username[25], password[10];
    float current_balance;
    // Skip header line
    fscanf(file, "%*[^\n]\n");

    while (fscanf(file, "%d, %24[^,], %9[^,], %f\n", &user_id, username, password, &current_balance) != EOF)
    {
        UserNode *new_user = create_user(user_id, username, password, current_balance);
        if (*head == NULL) {
            *head = new_user;  // The first user becomes the head of the list
        }
        else {
            UserNode* temp = *head;
            while (temp->next != NULL) {
                temp = temp->next;  // Traverse to the last user
            }
            temp->next = new_user;  // Add new user to the end of the list
        }
    }
    fclose(file);
}

/* Function to authenticate if the username and password entered by the user exist in the csv file 
and returns the user id when authenticated */
int User_Authentication(UserNode* head, const char* username, const char* password) {
    UserNode* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0 && strcmp(temp->password, password) == 0) {
            return temp->user_id;  // Return the user_id of the authenticated user
        }
        temp = temp->next;
    }
    return -1;  // Authentication failed
}

/* Function returns the current balance of a user based on the user id */
float Balance_Inquiry(UserNode* head, int user_id)
{
    UserNode* temp = head;
    while (temp != NULL) {
        if (temp->user_id == user_id) {
            return temp->current_balance;  // Return the balance of the user
        }
        temp = temp->next;
    }
    return -1;  // User not found
}

/* Function to update the user's balance based on the user id */
void Update_User_Balance(UserNode* head, int user_id, float amount)
{
    UserNode* temp = head;
    while (temp != NULL) {
        if (temp->user_id == user_id) {
            temp->current_balance += amount;  // Update the balance
            return;
        }
        temp = temp->next;
    }
}

/* Function to save the user's data to csv file */
void save_user_data_to_csv(const char* filename, UserNode* head) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Failed to open file: %s\n", filename);
        return;
    }

    // Write the header to CSV
    fprintf(file, "user_id,username,password,current_balance\n");

    UserNode* temp = head;
    while (temp != NULL) {
        fprintf(file, "%d,%s,%s,%.2f\n", temp->user_id, temp->username, temp->password, temp->current_balance);
        temp = temp->next;
    }
    fclose(file);  // Close the file after writing
}
