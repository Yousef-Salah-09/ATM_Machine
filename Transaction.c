#define _CRT_SECURE_NO_WARNINGS
#include "Transaction.h"
#include <stdio.h>
#include <string.h>

/* Function creates a transaction node by taking the transaction's data as an input */
TransactionNode* create_transaction(int transaction_id, int user_id, const char* type, float amount)
{
    TransactionNode* new_transaction = (TransactionNode*)malloc(sizeof(TransactionNode));
    if (new_transaction == 0) {
        printf("Memory allocation failed for transaction.\n");
        return 0;
    }

    new_transaction->transaction_id = transaction_id;
    new_transaction->user_id = user_id;
    strcpy(new_transaction->transaction_type, type);
    new_transaction->amount = amount;
    new_transaction->next = NULL;

    return new_transaction;
}

/* Function to add a new transaction to the linked list */
void add_transaction(TransactionNode** head, int transaction_id, int user_id, const char* type, float amount)
{
    TransactionNode* new_transaction = create_transaction(transaction_id, user_id, type, amount);

    if (*head == NULL) {
        *head = new_transaction; //The first transaction becomes the head of the list
    }
    else {
        TransactionNode* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next; // Traverse to the last transaction
        }
        temp->next = new_transaction;
    }
}

/* Function to save the transaction's data to csv file */
void save_transactions_to_csv(const char* filename, TransactionNode* head)
{
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Failed to open transaction file: %s\n", filename);
        return;
    }

    fprintf(file, "transaction_id,user_id,type,amount\n");
    TransactionNode* temp = head;
    while (temp != NULL) {
        fprintf(file, "%d,%d,%s,%.2f\n", temp->transaction_id, temp->user_id, temp->transaction_type, temp->amount);
        temp = temp->next;
    }

    fclose(file);
}

/* Function to load transactions from the csv to linked lists */
void load_transactions_from_csv(const char* filename, TransactionNode** head) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open transaction file: %s\n", filename);
        return;
    }

    int transaction_id, user_id;
    char type[10];
    float amount;

    // Skip header
    fscanf(file, "%*[^\n]\n");

    // Read transactions from the CSV and add to the linked list
    while (fscanf(file, "%d,%d,%9[^,],%f\n", &transaction_id, &user_id, type, &amount) != EOF) {
        add_transaction(head, transaction_id, user_id, type, amount);
    }

    fclose(file);
}

/* Function to view transactions for a specific user */
void view_transactions(TransactionNode* head, int user_id) {
    TransactionNode* temp = head;
    printf("\nTransaction History for User ID %d:\n", user_id);
    while (temp != NULL) {
        if (temp->user_id == user_id) {
            printf("Transaction ID: %d, Type: %s, Amount: %.2f\n", temp->transaction_id, temp->transaction_type, temp->amount);
        }
        temp = temp->next;
    }
}