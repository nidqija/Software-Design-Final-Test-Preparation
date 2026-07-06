#include <iostream>
#include <string>

using namespace std;

// ==========================================
// LOW-LEVEL MODULE (The Concrete Detail)
// ==========================================
class EmailNotificationService {
public:
    void sendEmail(const string& message) {
        cout << "Sending email notification: " << message << endl;
    }
};

// ==========================================
// CRITICAL DIP VIOLATION (High-Level Module)
// ==========================================
class NotificationManager {
private:
    // VIOLATION: We are directly depending on a specific low-level class 
    // instead of depending on an abstract interface.
    EmailNotificationService emailService; 

public:
    // The constructor doesn't take an abstraction; it is hardcoded to use emails.
    NotificationManager() {}

    void notifyUser(const string& message) {
        // High-level module knows exactly what low-level tool it is using.
        emailService.sendEmail(message); 
    }
};

// ==========================================
// MAIN ENGINE
// ==========================================
int main() {
    // Everything is hardwired together internally.
    NotificationManager manager;
    manager.notifyUser("Your order has been shipped!");

    // PROBLEM: If the business decides to switch from Email to SMS tomorrow, 
    // we cannot pass an SMS service into this manager. 
    // We would be forced to modify the internal code of NotificationManager, 
    // breaking its stability.

    return 0;
}