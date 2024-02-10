#include <iostream>
#include "person.h"

using namespace std;

// Person Class Methods

// Default constructor
Person::Person(){
    this->age = 0;
    this->name = "";
    this->place_of_birth = "";
    this->password = "";
    this->amount = 0.0;
}

// Parameterized constructor
Person::Person(int age, string name, string place_of_birth){
    this->age = age;
    this->name = name;
    this->place_of_birth = place_of_birth;
}

// Parameterized constructor with additional parameters
Person::Person(int age, string name, string place_of_birth, string password, float amount){
    this->age = age;
    this->name = name;
    this->place_of_birth = place_of_birth;
    this->password = password;
    this->amount = amount;
}

// Getters

// Getter for age
int Person::getAge() const {
    return age;
}

// Getter for name
string Person::getName() const {
    return name;
}

// Getter for place of birth
string Person::getPlaceOfBirth() const {
    return place_of_birth;
}

// Getter for password
string Person::getPassword() const {
    return password;
}

// Getter for amount
float Person::getAmount() const {
    return amount;
}

// Getter for transactions
Transactions Person::getTransactions() const {
    return transactions;
}

// Setters

// Setter for age
void Person::setAge(int newAge) {
    age = newAge;
}

// Setter for name
void Person::setName(const string& newName) {
    name = newName;
}

// Setter for place of birth
void Person::setPlaceOfBirth(const string& newPlaceOfBirth) {
    place_of_birth = newPlaceOfBirth;
}

// Setter for password
void Person::setPassword(const string& newPassword) {
    password = newPassword;
}

// Setter for amount
void Person::setAmount(float newAmount) {
    amount = newAmount;
}

// Setter for transactions
void Person::setTransactions(const Transactions& newTransactions) {
    transactions = newTransactions;
}

// Other Mandatory Methods

// Insert a new transaction
int Person::insert_transaction(string user, float amount, bool received){
    if(amount > this->amount){
        return 0;  // Insufficient funds
    }
    
    if(user == this->name){
        return -2;  // Cannot perform transaction to oneself
    }
    
    if(received){
        this->amount += amount;
    } else {
        this->amount -= amount;
    }
    
    // Create a new transaction node
    TransactionNode* new_transaction = new TransactionNode(user, amount, received);
    
    // Add the new transaction to the transactions list
    return transactions.add_transaction(new_transaction);
}

// Print details of the person
void Person::print_details(){
    cout << "Welcome " << this->name << "!" << endl;
    cout << "Your age is " << this->age << endl;
    cout << "You were born in the " << this->place_of_birth << endl;
    cout << fixed << setprecision(2) << "Your balance is " << this->amount << endl;
    
    // Print details of all transactions
    transactions.print_all_transaction();
}

// Check login credentials
bool Person::check_login(string n, string p){
    return n == name && password == p;
}

