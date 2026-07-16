#include <iostream>
#include <string>

using namespace std;


// 1. Factory Method Pattern
// The Factory Method Pattern is a creational design pattern that provides an interface for creating objects in a superclass, but allows subclasses to alter the type of objects that will be created.
// It promotes loose coupling by eliminating the need to bind application-specific classes into the code. The Factory Method lets a class defer instantiation to subclasses.

// Consequences for factory method pattern:
// 1. eliminates the need to bind application specific classes into the code
// 2. client might have to subclass the creator class to create a specific concrete product
// 3. provides hooks for subclasses to create extended versions of an object
// 4. connects parallel class hierarchies, which can be a source of complexity

// ==========================================
// 1. ABSTRACT PRODUCT
// ==========================================
class PaymentMethod {
public:
    virtual void processPayment(double amount) = 0;
    virtual ~PaymentMethod() {
        cout << "PaymentMethod base destroyed." << endl;
    }
};

// ==========================================
// 2. CONCRETE PRODUCTS
// ==========================================
class CreditCardPayment : public PaymentMethod {
public:
    void processPayment(double amount) override {
        cout << "Processing credit card payment of $" << amount << endl;
    }
    ~CreditCardPayment() override { cout << "CreditCardPayment object destroyed." << endl; }
};

class PayPalPayment : public PaymentMethod {
public:
    void processPayment(double amount) override {
        cout << "Processing PayPal payment of $" << amount << endl;
    }
    ~PayPalPayment() override { cout << "PayPalPayment object destroyed." << endl; }
};

// ==========================================
// 3. ABSTRACT CREATOR
// ==========================================
class PaymentProcessor {
public:
    // This is the actual "Factory Method"
    virtual PaymentMethod* createPaymentMethod() = 0; 

    // The Creator can also contain core business logic that works 
    // with whatever product the subclass decides to manufacture.
    void runTransaction(double amount) {
        // Call the factory method to manufacture a product dynamically
        PaymentMethod* method = createPaymentMethod();
        
        // Execute operation on the product
        method->processPayment(amount);
        
        // Clean up memory safely
        delete method;
    }

    virtual ~PaymentProcessor() = default;
};

// ==========================================
// 4. CONCRETE CREATORS
// ==========================================
class CreditCardProcessor : public PaymentProcessor {
public:
    // Overrides the abstract factory method to produce a CreditCardPayment object
    // subclass instantiates the product and returns it to the client
    PaymentMethod* createPaymentMethod() override {
        return new CreditCardPayment();
    }
};

class PayPalProcessor : public PaymentProcessor {
public:
    // Overrides the abstract factory method to produce a PayPalPayment object
    PaymentMethod* createPaymentMethod() override {
        return new PayPalPayment();
    }
};

// ==========================================
// CLIENT ENGINE
// ==========================================
int main() {
    cout << "--- Client initiates Credit Card pipeline ---" << endl;
    // Client selects which Concrete Creator it wants to use
    PaymentProcessor* processor1 = new CreditCardProcessor();
    processor1->runTransaction(100.0);
    delete processor1;

    cout << "\n--- Client initiates PayPal pipeline ---" << endl;
    PaymentProcessor* processor2 = new PayPalProcessor();
    processor2->runTransaction(200.0);
    delete processor2;

    return 0;
}