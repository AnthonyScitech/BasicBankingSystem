#ifndef DYNAMIC_LIST
#include <iostream>
#include "person.h"
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct Node{
	Person p;
	Node* next;
	
	Node(){
		next = nullptr;
	}
	
	Node(Person person){
		p = person;
		next = nullptr;
	}
};

class DynamicList{
	private:
		int size=0;
		Node* head;
		
		int add(Node* new_element, Node* next);
		bool check_name(string name, Node* next);
		Person* get_name_person(string name, Node* next);
		Person* check_login(string name, string password, Node* next);
		
	public:
		int add(Person p);
		bool check_name(string name);
		Person* get_name_person(string name);
		Person* check_login(string name, string password);
		
		void read_transactions_from_files();
		void read_users_from_file();
		void save_transactions_to_file();
		void save_users_to_file();
};


// Read user data from the file "users_data.txt"
void DynamicList::read_users_from_file() {
    ifstream inputFile("users_data.txt");

    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            istringstream iss(line);
            string token;

            Person person;

            // Tokenize the line using ',' as a delimiter
            vector<string> tokens;
            while (getline(iss, token, ',')) {
                tokens.push_back(token);
            }

            if (tokens.size() >= 5) {
                // Populate Person object with data from tokens
                person.setName(tokens[0]);
                person.setAmount(stof(tokens[4]));
                person.setAge(stoi(tokens[1]));
                person.setPassword(tokens[3]);
                person.setPlaceOfBirth(tokens[2]);

                // Add the person to the DynamicList
                add(person);
            }
        }

        inputFile.close();
    } else {
        cout << "Error: Unable to open the file." << endl;
    }
}

// Save user data to the file "users_data.txt"
void DynamicList::save_users_to_file() {
    ofstream userFile("users_data.txt");

    if (userFile.is_open()) {
        Node* current = head;

        // Iterate through the list and write each person's data to the file
        while (current != nullptr) {
            userFile << current->p.getName() << "," << current->p.getAge() << ","
                     << current->p.getPlaceOfBirth() << "," << current->p.getPassword() << ","
                     << current->p.getAmount() << "\n";
            current = current->next;
        }

        userFile.close();
    }
}

// Read user transactions from individual files
void DynamicList::read_transactions_from_files() {
    Node* current = this->head;

    // Iterate through each person in the DynamicList
    while (current != nullptr) {
        ifstream transactionFile(current->p.getName() + "-transactions.txt");

        if (transactionFile.is_open()) {
            string line;

            // Read each line from the transaction file and process transactions
            while (getline(transactionFile, line)) {
                istringstream iss(line);
                string token;

                // Tokenize the line using ',' as a delimiter
                vector<string> tokens;
                while (getline(iss, token, ',')) {
                    tokens.push_back(token);
                }

                if (tokens.size() >= 3) {
                    // Insert transaction for the current person
                    current->p.insert_transaction(tokens[0], stof(tokens[1]), (tokens[2] == "Yes" ? true : false));
                    cout << tokens[0] << " - " << stof(tokens[1]) << " - " << (tokens[2] == "Yes" ? true : false) << endl;
                }
            }

            transactionFile.close();
        } else {
            cout << "File Not Found or does not exist: " << (current->p.getName() + "-transactions.txt") << endl;
        }

        current = current->next;
    }
}

// Save user transactions to individual files
void DynamicList::save_transactions_to_file() {
    Node* current = head;

    // Iterate through each person in the DynamicList
    while (current != nullptr) {
        ofstream transactionFile(current->p.getName() + "-transactions.txt");

        if (transactionFile.is_open()) {
            // Iterate through user transactions
            TransactionNode* transaction = current->p.getTransactions().get_head();

            // Write each transaction to the corresponding transaction file
            while (transaction != nullptr) {
                transactionFile << transaction->get_user() << "," << transaction->get_amount() << ","
                                << (transaction->get_received() ? "Yes" : "No") << "\n";
                transaction = transaction->next;
            }

            transactionFile.close();
        }

        current = current->next;
    }
}

// Add a new person to the DynamicList
int DynamicList::add(Person p) {
    Node* new_node = new Node(p);

    // Check if the name is already present in the list
    if (check_name(p.getName())) {
        return 0; // Name already present
    }

    // If the list is empty, set the new node as the head
    if (head == nullptr) {
        head = new_node;
        return 1; // Successfully added
    }

    // Otherwise, add the new node to the list
    return add(new_node, head);
}

// Recursive function to add a new node to the DynamicList
int DynamicList::add(Node* new_element, Node* next) {
    // If the next node is the last node in the list, set the new node as its next
    if (next->next == nullptr) {
        next->next = new_element;
        return 1; // Successfully added
    }

    // Otherwise, continue recursively to find the last node
    return add(new_element, next->next);
}

// Check if a name is present in the DynamicList
bool DynamicList::check_name(string name) {
    // Start the check from the head of the list
    return check_name(name, head);
}

// Recursive function to check if a name is present in the DynamicList
bool DynamicList::check_name(string name, Node* next) {
    // If the end of the list is reached without finding the name, return false
    if (next == nullptr)
        return false;

    // If the name is found, return true
    if (next->p.getName() == name)
        return true;

    // Continue recursively to check the next node
    return check_name(name, next->next);
}

// Login Method
Person* DynamicList::check_login(string name, string password) {
    // Start the login check from the head of the list
    return check_login(name, password, head);
}

// Recursive function to check login credentials in the DynamicList
Person* DynamicList::check_login(string name, string password, Node* next) {
    // If the end of the list is reached without finding matching credentials, return nullptr
    if (next == nullptr) {
        return nullptr;
    }

    // If matching credentials are found, return a pointer to the corresponding Person object
    if (next->p.name == name && next->p.getPassword() == password) {
        return &next->p;
    }

    // Continue recursively to check the next node
    return check_login(name, password, next->next);
}

// Get Person by name
Person* DynamicList::get_name_person(string name) {
    // Start the search from the head of the list
    return get_name_person(name, head);
}

// Recursive function to get a Person by name in the DynamicList
Person* DynamicList::get_name_person(string name, Node* next) {
    // If the end of the list is reached without finding the name, return nullptr
    if (next == nullptr) {
        return nullptr;
    }

    // If the name is found, return a pointer to the corresponding Person object
    if (next->p.name == name) {
        return &next->p;
    }

    // Continue recursively to check the next node
    return get_name_person(name, next->next);
}

#endif // DYNAMIC_LIST

