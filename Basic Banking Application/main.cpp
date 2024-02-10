#include <iostream>
#include "dynamic_list.h"

using namespace std;

// Function Declarations
void login();
void register_user();
void make_transaction();

// Create an instance of DynamicList
DynamicList users_list;

// Login Function
void login() {
    string name;
    string password;
    cout << "***********Login***********" << endl;
    cout << "Enter Name: ";
    cin >> name;
    cout << "Password: ";
    cin >> password;
    cout << "Name: " << name << " password: " << password << endl;

    // Check login credentials
    Person* p = users_list.check_login(name, password);
    if (p != nullptr) {
        // Print user details if login is successful
        p->print_details();
    } else {
        cout << "Sorry, Invalid Credentials, Try Again" << endl;
    }
}

// Register User Function
void register_user() {
    string name;
    string password;
    string place_of_birth;
    int age;
    float amount;

    // Flashing Input Buffer
    cout << "***********Registration*************" << endl;
    cout << "Name: ";
    cin >> name;
    cout << "Age: ";
    cin >> age;
    cout << "Place of Birth: ";
    cin >> place_of_birth;
    cout << "Initial Balance: ";
    cin >> amount;
    cout << "Password: ";
    cin >> password;

    // Create a new Person object
    Person p(age, name, place_of_birth, password, amount);

    // Add the new user to the list
    if (users_list.add(p) == 0) {
        cout << "Name already exists, try with another name." << endl;
    } else {
        cout << "Thanks! Successfully added." << endl;
    }
}

// Make Transaction Function
void make_transaction() {
    string name;
    string password;
    cout << "***********Make Transaction***********" << endl;
    cout << "Enter Name: ";
    cin >> name;
    cout << "Password: ";
    cin >> password;

    // Check login credentials
    Person* p = users_list.check_login(name, password);
    if (p != nullptr) {
        cout << "----- Enter Receiver Details -----" << endl;
        string to_name;
        float to_amount;

        // Input receiver details
        cout << "Receiver Name: ";
        cin >> to_name;
        cout << "Sending Amount: ";
        cin >> to_amount;

        // Perform the transaction
        int result = p->insert_transaction(to_name, to_amount, false);
        if (result == 0) {
            cout << "Amount is not sufficient" << endl;
        } else if (result == -2) {
            cout << "Transaction cannot be made to oneself." << endl;
        } else {
            // Transaction successful, update the receiver's transactions
            Person* receiver = users_list.get_name_person(to_name);
            receiver->insert_transaction(name, to_amount, true);
            cout << "Transaction Successful" << endl;
        }
    } else {
        cout << "Sorry for the inconvenience, Invalid Credentials.\nPlease Try Again" << endl;
    }
}

// Main Function
int main() {
    // Reading Data from Stored Files
    users_list.read_users_from_file();
    users_list.read_transactions_from_files();

    // Main Program
    int option = 0;
    while (option != 4) {
        cout << "1- Login" << endl;
        cout << "2- Register" << endl;
        cout << "3- Make a Transaction" << endl;
        cout << "4- Exit" << endl;
        cin >> option;
        switch (option) {
            case 1: {
                login();
                break;
            }
            case 2: {
                register_user();
                break;
            }
            case 3: {
                make_transaction();
                break;
            }
            case 4: {
                // Save data to files before exiting
                users_list.save_transactions_to_file();
                users_list.save_users_to_file();
                break;
            }
            default: {
                cout << "Invalid Option Choice";
                break;
            }
        }
        cout << "================================" << endl;
    }
    cout << "Thanks for using our application." << endl;
    return 0;
}

