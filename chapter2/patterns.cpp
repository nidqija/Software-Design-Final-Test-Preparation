
// 8. Patterns
// standardized way to address solving a recurring problem in software engineering
// giving solution to problem
// a general reusable solution to a commonly occurring problem within a given context in software design

#include <iostream>
#include <string>

using namespace std;

// ==========================================
// THE SINGLETON PATTERN
// ==========================================
class ConfigurationManager {
private:
    string appVersion;
    string databaseURL;

    // RULE 1: Private constructor prevents anyone from using 'new ConfigurationManager()'
    ConfigurationManager() {
        appVersion = "v2.4.0";
        databaseURL = "mongodb://localhost:27017/prod_db";
        cout << "[System Log] Configuration Manager Initialized Once!" << endl;
    }

    // RULE 2: Delete copy constructor and assignment operator so copies cannot be made
    ConfigurationManager(const ConfigurationManager&) = delete;
    void operator=(const ConfigurationManager&) = delete;

public:
    // RULE 3: Provide a public, static method to get the single instance
    static ConfigurationManager& getInstance() {
        // This static instance is created exactly once, the first time this function is called
        static ConfigurationManager instance; 
        return instance;
    }

    // Example methods to simulate global configuration access
    string getAppVersion() const { return appVersion; }
    string getDatabaseURL() const { return databaseURL; }
    
    void setDatabaseURL(const string& newURL) { databaseURL = newURL; }
};

// ==========================================
// TEST UTILITIES (Simulating different systems)
// ==========================================
void runDatabaseSystem() {
    // Access the configuration manager from somewhere else in the codebase
    ConfigurationManager& config = ConfigurationManager::getInstance();
    cout << "[DB System] Connecting to: " << config.getDatabaseURL() << endl;
}

void runUIRenderer() {
    // Access the exact same configuration manager instance
    ConfigurationManager& config = ConfigurationManager::getInstance();
    cout << "[UI System] Rendering App Version: " << config.getAppVersion() << endl;
}

// ==========================================
// MAIN ENGINE
// ==========================================
int main() {
    cout << "--- Starting Application ---" << endl;

    // Try to access the settings from the UI layer
    runUIRenderer();

    // Try to access the settings from the Database layer
    runDatabaseSystem();

    // Modifying the single instance from anywhere changes it everywhere
    cout << "\n--- Updating Settings ---" << endl;
    ConfigurationManager::getInstance().setDatabaseURL("mongodb://192.168.1.50:27017/live_db");

    // Verify the database layer sees the update
    runDatabaseSystem();

    // CRITICAL PROOF: Un-commenting the line below will cause a compiler error!
    // ConfigurationManager myConfig; // Error: Constructor is private

    return 0;
}
