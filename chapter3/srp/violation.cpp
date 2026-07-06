#include <iostream>
#include <string>

using namespace std;

// ==========================================
// CRITICAL SRP VIOLATION
// ==========================================
class UserAccount {
private:
    string userName;

public:
    UserAccount(const string& name) : userName(name) {}

    // Job 1: User Management Logic
    void createUser() {
        // ... Simulate system saving user data ...

        // Job 2 & 3: Violates SRP by embedding formatting and direct console output!
        cout << "[INFO]: User '" << userName << "' created successfully." << endl;
    }

    // Job 1: User Management Logic
    void deleteUser() {
        // ... Simulate system deleting user data ...

        // Job 2 & 3: Violates SRP by embedding formatting and direct console output!
        cout << "[INFO]: User '" << userName << "' deleted successfully." << endl;
    }

    // Job 4 (Bonus Violation!): Unrelated logic mixed in
    // This gives the class yet another entirely different reason to change.
    void changeLogFormat() {
        cout << "Changing log style..." << endl; 
    }
};

// ==========================================
// MAIN ENGINE
// ==========================================
int main() {
    UserAccount user("Bob");
    user.createUser();
    user.deleteUser();

    return 0;
}