#include <iostream>
#include <string>

using namespace std;

// 3. Encapsulation
// Encapsulation binds data and the methods that manipulate that data together into a single unit (a class).
// By hiding internal details (using 'private'), we protect the data from unauthorized or accidental changes.

class BankAccount {
private:
    // HIDING THE DATA: These cannot be accessed directly from outside the class.
    // this is the essence of encapsulation: we control access to our data.
    string accountHolder;
    double balance;

public:
    // Constructor to initialize the securely encapsulated data
    BankAccount(string holder, double initialBalance) {
        accountHolder = holder;
        if (initialBalance >= 0) {
            balance = initialBalance;
        } else {
            balance = 0; // Guard rail against invalid initial data
        }
    }

    // PUBLIC INTERFACE: Safe, controlled ways to interact with the hidden data

    // Getter method: Allows people to look at the balance, but not change it directly
    double getBalance() {
        return balance;
    }

    // Controlled modification: You can't just set 'balance = 1000000'. You have to use deposit().
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited $" << amount << ". New balance: $" << balance << "\n";
        } else {
            cout << "Invalid deposit amount!\n";
        }
    }

    // Controlled modification with business logic rules built-in
    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount!\n";
        } else if (amount > balance) {
            cout << "Transaction Declined: Insufficient funds!\n";
        } else {
            balance -= amount;
            cout << "Withdrew $" << amount << ". Remaining balance: $" << balance << "\n";
        }
    }
};

int main() {
    BankAccount myAccount("Alice", 2000.00);

    // --- WHAT ENCAPSULATION PREVENTS ---
    // If the data wasn't hidden, a rogue line of code could do this:
    // myAccount.balance = -99999; // ERROR! Compiler won't allow this because 'balance' is private.

    // --- WHAT ENCAPSULATION ENFORCES ---
    // We must interact with the account using the safe public "steering wheels" provided:
    cout << "Initial Balance Check: $" << myAccount.getBalance() << "\n\n";

    cout << "--- Attempting a valid deposit ---\n";
    myAccount.deposit(150.00); 

    cout << "\n--- Attempting an illegal withdrawal ---\n";
    myAccount.withdraw(1000.00); // The class protects itself and denies this safely!

    return 0;
}