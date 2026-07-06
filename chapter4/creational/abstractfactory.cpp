#include <iostream>
#include <string>

using namespace std;



// 4. Abstract Factory Pattern
// provides an interface for creating families of related or dependent objects without specifying their concrete classes.

// Consequences for abstract factory pattern:
// 1. isolates concrete classes from the client code
// 2. makes exchanging product families easy


// ==========================================
// 1. ABSTRACT PRODUCTS
// ==========================================
class PaymentMethod {
public:
    virtual void processPayment(double amount) = 0;
    virtual ~PaymentMethod() = default;
};

class Receipt {
public:
    virtual void generateView() = 0;
    virtual ~Receipt() = default;
};

// ==========================================
// 2. CONCRETE PRODUCTS (Family A: Credit Card)
// ==========================================
class CreditCardPayment : public PaymentMethod {
public:
    void processPayment(double amount) override {
        cout << "Processing Credit Card transaction of $" << amount << endl;
    }
};

class PaperReceipt : public Receipt {
public:
    void generateView() override {
        cout << "Printing physical paper receipt to hardware console..." << endl;
    }
};

// ==========================================
// 3. CONCRETE PRODUCTS (Family B: PayPal)
// ==========================================
class PayPalPayment : public PaymentMethod {
public:
    void processPayment(double amount) override {
        cout << "Processing PayPal electronic transaction of $" << amount << endl;
    }
};

class DigitalReceipt : public Receipt {
public:
    void generateView() override {
        cout << "Generating encrypted digital PDF invoice for user email..." << endl;
    }
};

// ==========================================
// 4. THE ABSTRACT FACTORY
// ==========================================
// It defines interfaces to create a family of matching products
class TransactionFactory {
public:
    virtual PaymentMethod* createPayment() = 0;
    virtual Receipt* createReceipt() = 0;
    virtual ~TransactionFactory() = default;
};

// ==========================================
// 5. CONCRETE FACTORIES
// ==========================================
// Manufactures only Credit Card style products
class CreditCardFactory : public TransactionFactory {
public:
    PaymentMethod* createPayment() override { return new CreditCardPayment(); }
    Receipt* createReceipt() override { return new PaperReceipt(); }
};

// Manufactures only PayPal style products
class PayPalFactory : public TransactionFactory {
public:
    PaymentMethod* createPayment() override { return new PayPalPayment(); }
    Receipt* createReceipt() override { return new DigitalReceipt(); }
};

// ==========================================
// CLIENT SYSTEM
// ==========================================
// The client doesn't know or care about concrete product types. 
// It accepts any factory and handles execution seamlessly.
void executeCheckout(TransactionFactory* factory, double amount) {
    PaymentMethod* payment = factory->createPayment();
    Receipt* receipt = factory->createReceipt();

    payment->processPayment(amount);
    receipt->generateView();

    delete payment;
    delete receipt;
}

// ==========================================
// MAIN ENGINE
// ==========================================
int main() {
    cout << "--- Checkout Scenario 1: Retail Store Counter ---" << endl;
    TransactionFactory* retailStore = new CreditCardFactory();
    executeCheckout(retailStore, 45.50);
    delete retailStore;

    cout << "\n--- Checkout Scenario 2: E-Commerce Website ---" << endl;
    TransactionFactory* onlineStore = new PayPalFactory();
    executeCheckout(onlineStore, 120.00);
    delete onlineStore;

    return 0;
}