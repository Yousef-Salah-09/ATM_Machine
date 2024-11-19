#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "User.h"
#include "Transaction.h"
#include "util.h"

int main()
{
    UserNode* user_head = NULL;
    TransactionNode* transaction_head = NULL;

    /* Load user data and transaction history from users.csv and transactions.csv */
    load_transactions_from_csv("C:\\Users\\Salah\\Desktop\\yousef\\year 5 semester 1\\Advanced Embedded Systems\\ATM Project\\transactions.csv", &transaction_head);
    load_user_data_from_CSV("C:\\Users\\Salah\\Desktop\\yousef\\year 5 semester 1\\Advanced Embedded Systems\\ATM Project\\users_Encypted.csv", &user_head);
   
    /* To encrypt all the users passwords then save it to users_Encrypted.csv (used on first run only) */
  //  load_user_data_from_CSV("C:\\Users\\Salah\\Desktop\\yousef\\year 5 semester 1\\Advanced Embedded Systems\\ATM Project\\users.csv", &user_head);
  //  encryptPasswords(user_head);
  //  save_user_data_to_csv("C:\\Users\\Salah\\Desktop\\yousef\\year 5 semester 1\\Advanced Embedded Systems\\ATM Project\\users_Encypted.csv", user_head);

    int transaction_counter = 1;

    while (1)
    {
        char username[25], password[10];
        /* Take the username and password from the user */
        printf("Welcome to the ATM\n");
        printf("Enter your username:\n");
        scanf("%s", username);
        printf("Enter your password:\n");
        scanf("%s", password);

        /* Encrypt the user password to use it in authentication */
        char encryptedPassword[5];
        encryptPin(password, encryptedPassword);

        /* Authenticate the user */ 
        int user_id = User_Authentication(user_head, username, encryptedPassword);
        while (user_id == -1)
        {
            printf("Invalid username or password!\n");
            printf("Enter your username:\n");
            scanf("%s", username);
            printf("Enter your password:\n");
            scanf("%s", password);
            encryptPin(password, encryptedPassword);
            user_id = User_Authentication(user_head, username, encryptedPassword);
        }
   
        printf("Login successful!\n");

        int choice = 0;
        float amount;
        while (choice != 5)
        {
            printf("\nATM Menu:\n");
            printf("1. Check Balance\n");
            printf("2. Deposit Funds\n");
            printf("3. Withdraw Funds\n");
            printf("4. View Transaction History\n");
            printf("5. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            switch (choice) {
            case 1: {
                /* Check balance */ 
                float balance = Balance_Inquiry(user_head, user_id);
                printf("Your balance is: %.2f\n", balance);
                break;
            }
            case 2: {
                /* Deposit funds */
                printf("Enter amount to deposit: ");
                scanf("%f", &amount);
                Update_User_Balance(user_head, user_id, amount);
                add_transaction(&transaction_head, transaction_counter++, user_id, "deposit", amount);
                printf("Deposited %.2f to your account.\n", amount);
                break;
            }
            case 3: {
                /* Withdraw funds */ 
                printf("Enter amount to withdraw: ");
                scanf("%f", &amount);
                float balance = Balance_Inquiry(user_head, user_id);
                if (amount > balance) {
                    printf("Insufficient funds!\n");
                }
                else {
                    Update_User_Balance(user_head, user_id, -amount);
                    add_transaction(&transaction_head, transaction_counter++, user_id, "withdraw", amount);
                    printf("Withdrew %.2f from your account.\n", amount);
                }
                break;
            }
            case 4: {
                /* View transaction history */
                view_transactions(transaction_head, user_id);
                break;
            }
            case 5: {
                /* Exit */
                printf("Exiting...\n\n\n");
                break;
            }
            default:
                printf("Invalid choice. Please try again.\n");
            }
        }
        /* Saving the user and transaction data to the csv files */
        save_user_data_to_csv("C:\\Users\\Salah\\Desktop\\yousef\\year 5 semester 1\\Advanced Embedded Systems\\ATM Project\\users_Encypted.csv", user_head);
        save_transactions_to_csv("C:\\Users\\Salah\\Desktop\\yousef\\year 5 semester 1\\Advanced Embedded Systems\\ATM Project\\transactions.csv", transaction_head);
    }
}