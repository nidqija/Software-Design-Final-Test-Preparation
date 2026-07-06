#include <iostream>

using namespace std;


// 5. Dependency Inversion Principle (DIP)
// High-level modules should not depend on low-level modules. Both should depend on abstractions (e.g., interfaces).
// meaning that high level modules shouldnt know what type of low level modules they are using , they should only know about the abstraction of the low level modules



// benefit of DIP
// 1. Flexibility: High-level modules can work with any low-level module that adheres to the same interface, making it easier to swap out implementations without changing the high-level code.
// 2. Testability: By depending on abstractions, high-level modules can be tested in isolation using mock implementations of the low-level modules.
// 3. Maintainability: Changes in low-level modules do not affect high-level modules as long as the interface remains consistent, reducing the risk of introducing bugs when modifying code.


// disadvatages of DIP
// 1. Increased Complexity: Introducing abstractions can add complexity to the codebase, making it harder to understand for developers who are not familiar with the design pattern.
// 2. Overhead: The use of interfaces and abstractions can introduce additional layers of indirection, which may impact performance in certain scenarios.
// 3. Learning Curve: Developers may need to learn and understand the principles of dependency inversion

class INotificationService {
    public:
        virtual void sendNotification(const std::string& message) = 0; // Pure virtual function for sending notifications
        virtual ~INotificationService() = default; // Virtual destructor for proper cleanup

};


class EmailNotificationService : public INotificationService {
    public:
        void sendNotification(const std::string& message) override {
            cout << "Sending email notification: " << message << endl;
        }
};


class SMSNotificationService : public INotificationService {
    public:
        void sendNotification(const std::string& message) override {
            cout << "Sending SMS notification: " << message << endl;
        }
};


class NotificationManager {
    private:
        INotificationService* notificationService; // Dependency on the abstraction

    public:
        NotificationManager(INotificationService* service) : notificationService(service) {}

        void notifyUser(const std::string& message) {
            notificationService->sendNotification(message); // Use the abstraction to send notifications
        }
};



int main(){
    
    // Using EmailNotificationService
    EmailNotificationService emailService;
    // use object pointer to pass the dependency to the high level module
    // & symbol is used to get the address of the object and pass it to the constructor of NotificationManager
    NotificationManager emailManager(&emailService);
    emailManager.notifyUser("Your order has been shipped!");

    // Using SMSNotificationService
    SMSNotificationService smsService;
    NotificationManager smsManager(&smsService);
    smsManager.notifyUser("Your package will arrive tomorrow!");

    return 0;
}