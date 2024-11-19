#pragma once
#include <stdlib.h>

/* UserNode struct for the required data architecture */
typedef struct UserNode {
    int user_id;
    char username[25];
    char password[10];
    float current_balance;
    struct UserNode* next;
} UserNode;

/* Functions prototypes */
UserNode* create_user(int user_id, const char* username, const char* password, float current_balance);
void load_user_data_from_CSV(const char* filename, UserNode** head);
int User_Authentication(UserNode* head, const char* username, const char* password);
float Balance_Inquiry(UserNode *head, int user_id);
void Update_User_Balance(UserNode* head, int user_id, float amount);
void save_user_data_to_csv(const char* filename, UserNode* head);
