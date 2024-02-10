#ifndef PERSON

#include <iostream>
#include "transaction.h"

using namespace std;

// Person Class Declaration

class Person {
public:
    // Constructors
    Person();  // Default constructor
    Person(int age, string name, string place_of_birth);  // Parameterized constructor
    Person(int age, string name, string place_of_birth, string password, float amount);  // Parameterized constructor

    // Transaction methods
    int insert_transaction(string user, float amount, bool received);  // Insert a new transaction
    void print_details();  // Print details of the person
    bool check_login(string n, string p);  // Check login credentials

    // Getters
    int getAge() const;  // Getter for age
    string getName() const;  // Getter for name
    string getPlaceOfBirth() const;  // Getter for place of birth
    string getPassword() const;  // Getter for password
    float getAmount() const;  // Getter for amount
    Transactions getTransactions() const;  // Getter for transactions

    // Setters
    void setAge(int newAge);  // Setter for age
    void setName(const string& newName);  // Setter for name
    void setPlaceOfBirth(const string& newPlaceOfBirth);  // Setter for place of birth
    void setPassword(const string& newPassword);  // Setter for password
    void setAmount(float newAmount);  // Setter for amount
    void setTransactions(const Transactions& newTransactions);  // Setter for transactions

    string name;  // Public variable for name

private:
    // Private member variables
    int age;
    string place_of_birth;
    string password;
    float amount = 0.0;
    Transactions transactions;  // Object to manage person's transactions
};

#endif // PERSON

