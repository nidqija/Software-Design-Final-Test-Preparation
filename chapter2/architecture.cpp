#include <iostream>

using namespace std;

// 7. Architecture
// complete structure of software is known as software architecture
// provides conceptual integrity for a system in a number of ways
// also is a structure at program modules where they interact with each other in a specialized way

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ==========================================
// THE DATA MODEL
// ==========================================
struct User {
    int id;
    string name;
};

// ==========================================
// 1. DATA ACCESS LAYER (Repository)
// ==========================================
// Responsibility: Purely handles database simulation or data persistence.
// It knows NOTHING about business rules or UI.
class UserRepository {
private:
    vector<User> database; // Simulating a real database table
public:
    void save(const User& user) {
        database.push_back(user);
    }
    
    vector<User> fetchAll() const {
        return database;
    }
};

// ==========================================
// 2. BUSINESS LOGIC LAYER (Service)
// ==========================================
// Responsibility: Enforces application rules and processes data.
// It interacts with the Data Layer, but knows NOTHING about the UI.
class UserService {
private:
    UserRepository& repo; // Specialized interaction with the Data Layer
public:
    UserService(UserRepository& repository) : repo(repository) {}

    void registerUser(int id, string name) {
        // Business Rule: Ensure user has a valid name before saving
        if (name.empty()) {
            cerr << "[Service Error] Cannot register user with an empty name!" << endl;
            return;
        }
        
        User newUser = {id, name};
        repo.save(newUser); // Delegate to Data Layer
        cout << "[Service Log] Business rules passed. User saved." << endl;
    }

    vector<User> getAllRegisteredUsers() {
        return repo.fetchAll();
    }
};

// ==========================================
// 3. PRESENTATION LAYER (UI / View)
// ==========================================
// Responsibility: Displays information and catches user input.
// It interacts only with the Business Layer.
class UserConsoleUI {
private:
    UserService& service; // Specialized interaction with the Business Layer
public:
    UserConsoleUI(UserService& userService) : service(userService) {}

    void showRegistrationForm() {
        cout << "\n=== User Registration Screen ===" << endl;
        service.registerUser(101, "Alice");
        service.registerUser(102, "Bob");
        service.registerUser(103, ""); // This should trigger a business rule failure
    }

    void displayUserDashboard() {
        cout << "\n=== Registered Users Dashboard ===" << endl;
        vector<User> users = service.getAllRegisteredUsers();
        for (const auto& user : users) {
            cout << "ID: " << user.id << " | Name: " << user.name << endl;
        }
    }
};

// ==========================================
// THE SYSTEM ENGINE (Bootstrapping the Architecture)
// ==========================================
int main() {
    // 1. Initialize the Data Layer
    UserRepository databaseRepo;

    // 2. Inject Data Layer into Business Layer
    UserService userBusinessService(databaseRepo);

    // 3. Inject Business Layer into Presentation Layer
    UserConsoleUI userInterface(userBusinessService);

    // 4. Run the application
    userInterface.showRegistrationForm();
    userInterface.displayUserDashboard();

    return 0;
}