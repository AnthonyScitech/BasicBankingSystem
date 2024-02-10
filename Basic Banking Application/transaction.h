#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Structure to represent a node in the transactions list
struct TransactionNode {
    string user;     // User involved in the transaction
    float amount;    // Amount of the transaction
    bool received;   // Flag indicating whether the user received the amount (true) or paid the amount (false)

    TransactionNode* next;  // Pointer to the next transaction node in the list

    // Default constructor
    TransactionNode() {
        this->received = false;
        this->next = nullptr;
        this->user = "";
        this->amount = 0.0;
    }

    // Parameterized constructor
    TransactionNode(string u, int amount, bool received) {
        this->received = received;
        this->amount = amount;
        this->next = nullptr;
        this->user = u;
    }

    // Method to print details of a transaction node
    void print();

    // Getter and setter methods for user
    void set_user(string user);
    string get_user();

    // Getter and setter methods for amount
    void set_amount(float amount);
    float get_amount();

    // Getter and setter methods for received flag
    void set_received(bool received);
    bool get_received();
};

// Class to manage a list of transactions
class Transactions {
public:
    int add_transaction(TransactionNode* new_transaction);  // Add a new transaction to the list
    void print_all_transaction();  // Print details of all transactions in the list
    TransactionNode* get_head();   // Getter for the head of the transactions list

private:
    TransactionNode* head = nullptr;  // Pointer to the head of the transactions list
    int transactions = 0;             // Count of transactions in the list
};

#endif // TRANSACTION_H

