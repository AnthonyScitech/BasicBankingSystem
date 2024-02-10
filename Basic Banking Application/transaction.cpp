#include <iostream>
#include "transaction.h"

using namespace std;

// TransactionNode Class Methods

// Print details of a transaction node
void TransactionNode::print() {
    cout << "Your transactions are" << endl;
    cout << fixed << setprecision(2) << (this->received ? "\t- FROM " : "\t- TO ")
         << this->user << " you " << (this->received ? "received £" : "paid £") << this->amount << endl;
}

// Getter for transaction amount
float TransactionNode::get_amount() {
    return this->amount;
}

// Setter for transaction amount
void TransactionNode::set_amount(float amount) {
    this->amount = amount;
}

// Getter for transaction type (received or not)
bool TransactionNode::get_received() {
    return this->received;
}

// Setter for transaction type (received or not)
void TransactionNode::set_received(bool received) {
    this->received = received;
}

// Getter for the user involved in the transaction
string TransactionNode::get_user() {
    return this->user;
}

// Setter for the user involved in the transaction
void TransactionNode::set_user(string user) {
    this->user = user;
}

// Transactions Class Methods

// Getter for the head of the transaction list
TransactionNode* Transactions::get_head() {
    return Transactions::head;
}

// Add a new transaction to the list
int Transactions::add_transaction(TransactionNode* new_transaction) {
    // Set the next pointer of the new transaction to the current head
    new_transaction->next = head;

    // Update the head to point to the new transaction
    head = new_transaction;

    // Increment the transaction count
    transactions++;

    return 1; // Success Code
}

// Print details of all transactions in the list
void Transactions::print_all_transaction() {
    if (Transactions::head == nullptr) {
        cout << "No transactions to display" << endl;
        return;
    }

    TransactionNode* current = head;

    // Iterate through the list and print details of each transaction
    while (current != nullptr) {
        current->print();
        current = current->next;
    }
}

