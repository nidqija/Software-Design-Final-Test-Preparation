#include <iostream>
#include <string>

using namespace std;

// --- PRODUCT ---
// The interface of objects the Factory Method creates [1]
class IPaymentMethod {
public:
    virtual void processOrder(double amount) = 0;
    virtual ~IPaymentMethod() {} 
};

// --- CONCRETE PRODUCTS ---
// Implement the IPaymentMethod interface [1]
class CreditCardPayment : public IPaymentMethod {
public:
    void processOrder(double amount) override {
        cout << "Processing credit card payment of $" << amount << endl;
    }
};

class PayPalPayment : public IPaymentMethod {
public:
    void processOrder(double amount) override {
        cout << "Processing PayPal payment of $" << amount << endl;
    }
};

// --- CREATOR ---
// Declares the factory method which returns a Product [1]
class PaymentProcessor {
public:
    // This is the Factory Method [4]
    virtual IPaymentMethod* createPaymentMethod() = 0;

    // The Creator can also contain high-level logic that uses the product
    void processPayment(double amount) {
        IPaymentMethod* method = createPaymentMethod(); // Deferring instantiation to subclasses [3]
        method->processOrder(amount);
        delete method;
    }
    virtual ~PaymentProcessor() {}
};

// --- CONCRETE CREATORS ---
// Overrides the factory method to return a ConcreteProduct [5]
class CreditCardProcessor : public PaymentProcessor {
public:
    IPaymentMethod* createPaymentMethod() override {
        return new CreditCardPayment();
    }
};

class PayPalProcessor : public PaymentProcessor {
public:
    IPaymentMethod* createPaymentMethod() override {
        return new PayPalPayment();
    }
};

// --- CLIENT ---
int main() {
    // The client chooses which Processor (Creator) to use [6]
    PaymentProcessor* processor1 = new CreditCardProcessor();
    processor1->processPayment(100.0);

    PaymentProcessor* processor2 = new PayPalProcessor();
    processor2->processPayment(200.0);

    delete processor1;
    delete processor2;

    return 0;
}