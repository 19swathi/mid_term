#include <iostream>
using namespace std;

// Node structure for the linked list
struct Transaction {
    string type;            // Type of transaction (e.g., "Deposit", "Withdrawal")
    double amount;          // Amount of the transaction
    Transaction* next;      // Pointer to the next transaction node
};

class TransactionManager {
private:
    Transaction* head;      // Pointer to the head of the transaction linked list
    double balance;         // Current balance in the account

public:
    // Constructor to initialize the TransactionManager object
    TransactionManager() {
        head = nullptr;     // Initialize head pointer to nullptr
        balance = 0.0;      // Initialize balance to zero
    }

    // Function to perform a deposit transaction
    void deposit(double amount) {
        Transaction* newNode = new Transaction;     // Create a new transaction node
        newNode->type = "Deposit";                  // Set transaction type to "Deposit"
        newNode->amount = amount;                   // Set transaction amount
        newNode->next = nullptr;                    // Initialize next pointer to nullptr

        // If the linked list is empty, set the new node as the head
        if (head == nullptr) {
            head = newNode;
        }
        // Otherwise, add the new node at the beginning of the linked list
        else {
            newNode->next = head;
            head = newNode;
        }
        // Update the account balance
        balance += amount;
    }

    // Function to perform a withdrawal transaction
    void withdraw(double amount) {
        // Check if the account balance is sufficient for withdrawal
        if (balance >= amount) {
            Transaction* newNode = new Transaction;     // Create a new transaction node
            newNode->type = "Withdrawal";               // Set transaction type to "Withdrawal"
            newNode->amount = amount;                   // Set transaction amount
            newNode->next = nullptr;                    // Initialize next pointer to nullptr

            // If the linked list is empty, set the new node as the head
            if (head == nullptr) {
                head = newNode;
            }
            // Otherwise, add the new node at the beginning of the linked list
            else {
                newNode->next = head;
                head = newNode;
            }
            // Update the account balance
            balance -= amount;
        }
        else {
            cout << "Insufficient balance!" << endl;     // Display error message if balance is insufficient
        }
    }

    // Function to display all transactions
    void displayTransactions() {
        Transaction* temp = head;   // Initialize a temporary pointer to traverse the linked list
        // Traverse the linked list and display each transaction
        while (temp != nullptr) {
            cout << temp->type << " : " << temp->amount << endl;
            temp = temp->next;
        }
    }

    // Function to check the account balance
    double getBalance() {
        return balance;     // Return the current balance
    }

    // Destructor to free memory allocated for the linked list
    ~TransactionManager() {
        Transaction* temp;      // Temporary pointer to traverse the linked list
        // Traverse the linked list and delete each node
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    TransactionManager manager;     // Create a TransactionManager object
    int choice;                     // Variable to store user's choice
    double amount;                  // Variable to store transaction amount

    // Display menu and process user's choice until the user chooses to exit
    do {
        // Display menu options
        cout << "\nBanking System Menu:" << endl;
        cout << "1. Deposit" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Display Transactions" << endl;
        cout << "4. Check Balance" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;      // Read user's choice from the standard input

        // Perform actions based on user's choice
        switch (choice) {
        case 1:     // Deposit
            cout << "Enter amount to deposit: ";
            cin >> amount;              // Read deposit amount from the standard input
            manager.deposit(amount);   // Perform deposit transaction
            cout << "Deposit successful!" << endl;   // Display success message
            break;
        case 2:     // Withdraw
            cout << "Enter amount to withdraw: ";
            cin >> amount;              // Read withdrawal amount from the standard input
            manager.withdraw(amount);  // Perform withdrawal transaction
            break;
        case 3:     // Display Transactions
            cout << "All Transactions:" << endl;
            manager.displayTransactions();     // Display all transactions
            break;
        case 4:     // Check Balance
            cout << "Current Balance: $" << manager.getBalance() << endl;    // Display current balance
            break;
        case 5:     // Exit
            cout << "Exiting..." << endl;   // Display exit message
            break;
        default:    // Invalid choice
            cout << "Invalid choice! Please try again." << endl;    // Display error message
            break;
        }
    } while (choice != 5);      // Continue the loop until the user chooses to exit

    return 0;   // Return 0 to indicate successful program execution
}