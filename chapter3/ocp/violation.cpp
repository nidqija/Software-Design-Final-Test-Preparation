#include <iostream>
#include <string>

using namespace std;

// Enum representing types of payments
enum PaymentType {
    CREDIT_CARD,
    PAYPAL
};

// ==========================================
// CRITICAL OCP VIOLATION
// ==========================================
class PaymentProcessor {
public:
    // This function is NOT closed for modification!
    void process(PaymentType type, double amount) {
        switch (type) {
            case CREDIT_CARD:
                cout << "Processing credit card payment of $" << amount << endl;
                break;

            case PAYPAL:
                cout << "Processing PayPal payment of $" << amount << endl;
                break;

            // PROBLEM: Every single time the business wants to accept a new payment method 
            // (like Crypto or ApplePay), we are FORCED to open up this file, 
            // modify this switch statement, add a new case, and risk breaking existing code.
        }
    }
};

// ==========================================
// MAIN ENGINE
// ==========================================
int main() {
    PaymentProcessor processor;

    // Processing different payments through a rigid, unextendable class
    processor.process(CREDIT_CARD, 100.0);
    processor.process(PAYPAL, 200.0);

    return 0;
}