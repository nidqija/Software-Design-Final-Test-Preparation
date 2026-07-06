#include <iostream>
#include <string>

using namespace std;

// 3. Singleton Pattern
// ensure a class has only one instance and surround a global point of access to it.



// benefits of singleton pattern:
// 1. Controlled access to sole instance
// 2. Reduced namespace pollution (no global variables)
// 3. can permit a variable number of instances (if needed) by modifying the implementation


// ==========================================
// THE SINGLETON CLASS
// ==========================================
class DatabaseConnection {
private:
    string connectionString;
    bool isConnected;

    // RULE 1: Private constructor prevents outside code from using 'new DatabaseConnection()'
    DatabaseConnection() {
        connectionString = "jdbc:mysql://localhost:3306/production_db";
        isConnected = true;
        cout << "[System Log] Connected to Database Server safely." << endl;
    }

    // RULE 2: Delete copy constructor and assignment operator. 
    // This stops anyone from duplicating the instance via copying.
    DatabaseConnection(const DatabaseConnection&) = delete;
    void operator=(const DatabaseConnection&) = delete;

public:
    // RULE 3: Provide a public, static method to get the single instance.
    // static is declared as it cannot be tied to a specific object instance (since there is only one).
    // it can be called without creating an object of the class.
    static DatabaseConnection& getInstance() {
        // Created exactly once the first time this function is executed
        static DatabaseConnection instance; 
        return instance;
    }

    // Example operational methods
    void executeQuery(const string& sql) {
        if (isConnected) {
            cout << "[Query Executed] -> " << sql << endl;
        }
    }

    string getConnectionString() const { return connectionString; }
};

// ==========================================
// CLIENT MODULES
// ==========================================
void loadUserProfile() {
    // Accessing the singleton instance from the UI layer
    DatabaseConnection& db = DatabaseConnection::getInstance();
    db.executeQuery("SELECT * FROM users WHERE id = 42;");
}

void loadInventoryData() {
    // Accessing the exact same singleton instance from the Warehouse layer
    DatabaseConnection& db = DatabaseConnection::getInstance();
    db.executeQuery("SELECT * FROM products WHERE stock < 5;");
}





// ==========================================
// MAIN ENGINE
// ==========================================
int main() {
    cout << "--- Initializing Application Lifecycle ---" << endl;

    // Notice that the constructor log only appears once, right here:
    loadUserProfile();
    
    
    cout << "\n--- Fetching Next System Submodule ---" << endl;
    loadInventoryData();

    cout << "\nDatabase URL in use: " << DatabaseConnection::getInstance().getConnectionString() << endl;

    // CRITICAL PROOF: Un-commenting either line below triggers a compilation error!
    // DatabaseConnection cluster;               // Error: Private constructor
    // DatabaseConnection copy = DatabaseConnection::getInstance(); // Error: Deleted copy constructor

    return 0;
}