#include <stdlib.h>

/* TransactionNode struct for the required data architecture */
typedef struct TransactionNode {
    int transaction_id;
    char transaction_type[10];
    float amount;
    int user_id;
    struct TransactionNode* next;
} TransactionNode;

/* Functions prototypes */
TransactionNode* create_transaction(int transaction_id, int user_id, const char* type, float amount);
void add_transaction(TransactionNode** head, int transaction_id, int user_id, const char* type, float amount);
void save_transactions_to_csv(const char* filename, TransactionNode* head);
void load_transactions_from_csv(const char* filename, TransactionNode** head);
void view_transactions(TransactionNode* head, int user_id);