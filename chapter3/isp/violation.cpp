#include <iostream>
#include <string>

using namespace std;

// ==========================================
// CRITICAL ISP VIOLATION (Fat Interface)
// ==========================================
class IPaymentSystem {
public:
    virtual void processPayment() = 0;
    virtual void printReceipt() = 0;      // Physical printer action
    virtual void generateReceipt() = 0;   // Digital QR screen action
    
    virtual ~IPaymentSystem() = default;
};

// ==========================================
// CONCRETE IMPLEMENTATIONS (Forced Dependencies)
// ==========================================

class CreditCardPayment : public IPaymentSystem {
private:
    double amount;
public:
    CreditCardPayment(double amt) : amount(amt) {}

    void processPayment() override {
        cout << "Processing credit card payment of $" << amount << endl;
    }

    void printReceipt() override {
        cout << "Printing credit card receipt" << endl;
    }

    // VIOLATION: Credit cards don't use digital QR generation!
    // We are forced to write a dummy method to appease the compiler.
    void generateReceipt() override {
        // Do nothing or throw an error
        cerr << "[ISP Warning] Credit Card does not support digital QR receipts!" << endl;
    }
};

class QRPayment : public IPaymentSystem {
private:
    double amount;
public:
    QRPayment(double amt) : amount(amt) {}

    void processPayment() override {
        cout << "Processing QR payment of $" << amount << endl;
    }

    // VIOLATION: QR payments do not print physical hardware paper receipts!
    // We are forced to implement this useless method.
    void printReceipt() override {
        // Do nothing or throw an error
        cerr << "[ISP Warning] QR Payment cannot print a physical receipt!" << endl;
    }

    void generateReceipt() override {
        cout << "Generating QR receipt for $" << amount << endl;
    }
};

// ==========================================
// MAIN ENGINE
// ==========================================
int main() {
    cout << "--- Processing Credit Card ---" << endl;
    IPaymentSystem* card = new CreditCardPayment(100.0);
    card->processPayment();
    card->printReceipt();
    // A client can accidentally invoke a useless method because of the fat interface
    card->generateReceipt(); 

    cout << "\n--- Processing QR Code ---" << endl;
    IPaymentSystem* qr = new QRPayment(200.0);
    qr->processPayment();
    qr->generateReceipt();
    // A client can accidentally invoke a useless method because of the fat interface
    qr->printReceipt(); 

    delete card;
    delete qr;
    return 0;
}