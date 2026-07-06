#include <iostream>

using namespace std;


// 1. Single Responsibility Principle (SRP)
// The Single Responsibility Principle states that a class should have only one reason to change,
// it should only have one job or responsibility. This principle promotes high cohesion and low coupling, 
// making the code easier to maintain and understand.


// benefit of SRP
// 1. Maintainability: When a class has a single responsibility, it is easier to understand and modify without affecting other parts of the system.
// 2. Testability: Classes with a single responsibility are easier to test in isolation,
// 3. Reusability: A class with a single responsibility can be reused in different contexts without bringing along unrelated functionality.


// disadbantages of SRP
// 1. Increased Number of Classes: Following SRP can lead to a larger number of classes in the system, which may increase complexity in terms of navigation and understanding the overall architecture.
// 2. Overhead in Communication: If multiple classes are created to handle different responsibilities, there may be increased communication overhead between these classes, leading to potential performance issues.
// 3. Initial Learning Curve: Developers may need to spend more time understanding the relationships between classes and how they interact, especially in larger systems with many single-responsibility classes.


// SRP use case 1
// Logger class is responsible for logging messages
class Logger {
    public:
        void logInfo(const string& message) {
            cout << "[INFO]: " << message << endl;
        }

        void logError(const string& message) {
            cerr << "[ERROR]: " << message << endl;
        }
};


// SRP use case 2
// UserManager class is responsible for user management
class UserManager{
    private:
        string userName;
        string message;
        Logger logger;


    public:
    
        UserManager(const string& name) : userName(name) {}

        void createUser() {
            // Simulate user creation logic
            message = "User '" + userName + "' created successfully.";
            logger.logInfo(message);
        }

        void deleteUser() {
            // Simulate user deletion logic
            message = "User '" + userName + "' deleted successfully.";
            logger.logInfo(message);
        }
        
};


// main function to demonstrate SRP
int main(){
    
    UserManager userManager("Alice");
    userManager.createUser();
    userManager.deleteUser();

    return 0;
}