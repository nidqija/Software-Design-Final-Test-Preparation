#include <iostream>
#include <memory>
#include <string>

using namespace std;

// Strategy Design Pattern
// Intent Define a family of algorithms, encapsulate each one, and make them interchangeable. 
// Strategy lets the algorithm vary independently from clients that use it.

    


// Example use case for strategy design pattern:
// 1. Payment Processing: An e-commerce application can use the Strategy pattern to handle different payment methods (e.g., credit card, PayPal, cryptocurrency). Each payment method can be encapsulated in its own strategy class, allowing the application to switch between them seamlessly.'
// 2. Report Format Generation: A reporting system can use the Strategy pattern to generate reports in different formats (e.g., PDF, Excel, HTML). Each format can be implemented as a separate strategy, enabling users to choose their preferred output format at runtime.
// 3. Sorting Algorithms: A data processing application can use the Strategy pattern to allow users to select different sorting algorithms (e.g., quicksort, mergesort, heapsort) based on their specific needs. Each sorting algorithm can be encapsulated in its own strategy class, providing flexibility in choosing the most efficient algorithm for a given dataset.

// Consequences of using the Strategy Design Pattern:
// 1. Flexibility: The Strategy pattern allows you to change the behavior of a class at runtime by switching between different strategies.
// 2. Encapsulation: Each strategy is encapsulated in its own class, promoting separation of concerns and making the code easier to maintain.
// 3. Open/Closed Principle: You can introduce new strategies without modifying existing code, adhering to the open/closed principle.
// 4. Increased Complexity: The pattern can introduce additional classes and interfaces, which may increasez the complexity of the codebase, especially for simple scenarios.

// Components of the Strategy Design Pattern:
// 1. Strategy Interface: Defines a common interface for all supported algorithms.
// 2. Concrete Strategies: Implement the Strategy interface with specific algorithms.
// 3. Context: Maintains a reference to a Strategy object and can switch between strategies at runtime.
// 4. Client: Configures the Context with a specific Strategy and invokes the algorithm.


// ==========================================
// 1. Strategy Interface
// ==========================================
// This defines the common interface for all supported algorithms.
class PaymentStrategy {
public:
    virtual void pay(int amount) = 0;
    virtual ~PaymentStrategy() = default; // Virtual destructor for safety
};


// ==========================================
// 2. Concrete Strategies
// ==========================================
// Encapsulates a specific payment behavior.
class CreditCardPayment : public PaymentStrategy {
private:
    string name;
    string cardNumber;
public:
    CreditCardPayment(string name, string cardNumber) 
        : name(name), cardNumber(cardNumber) {}

    void pay(int amount) override {
        cout << "Paid $" << amount << " using Credit Card (" << cardNumber << ")\n";
    }
};

class PayPalPayment : public PaymentStrategy {
private:
    string email;
public:
    PayPalPayment(string email) : email(email) {}

    void pay(int amount) override {
        cout << "Paid $" << amount << " using PayPal account (" << email << ")\n";
    }
};

class BitcoinPayment : public PaymentStrategy {
    private:
    string walletAddress;

    public:
    BitcoinPayment(string walletAddress) : walletAddress(walletAddress) {}

    void pay(int amount) override {
        cout << "Paid $" << amount << " using Bitcoin wallet (" << walletAddress << ")\n";
    }
};


// ==========================================
// 3. Context
// ==========================================
// This is the class that configures and uses a Strategy.
class ShoppingCart {
private:
    int totalAmount = 0;
    shared_ptr<PaymentStrategy> paymentMethod; // Reference to the current strategy
public:
    void addAmount(int price) {
        totalAmount += price;
    }

    // Dynamic strategy swapping at runtime
    void setPaymentMethod(shared_ptr<PaymentStrategy> method) {
        paymentMethod = method;
    }

    void checkout() {
        if (!paymentMethod) {
            cout << "Error: Please select a payment method before checking out!\n";
            return;
        }
        // Delegate the work to the strategy object
        paymentMethod->pay(totalAmount);
        totalAmount = 0; // Reset cart
    }
};


// ==========================================
// Client Code
// ==========================================
int main() {
    ShoppingCart cart;
    cart.addAmount(100);
    cart.addAmount(45); // Total cart = $145

    // Scenario A: Customer wants to use Credit Card
    cout << "--- Selecting Credit Card Strategy ---" << endl;
    auto cardStrategy = make_shared<CreditCardPayment>("Alice Smith", "1234-5678-9012-3456");
    cart.setPaymentMethod(cardStrategy);
    cart.checkout();

    cout << "\n--- New Shopping Session ---" << endl;
    cart.addAmount(250); // Total cart = $250

    // Scenario B: Customer switches to PayPal at runtime
    cout << "--- Switching to PayPal Strategy ---" << endl;
    auto paypalStrategy = make_shared<PayPalPayment>("alice.smith@example.com");
    cart.setPaymentMethod(paypalStrategy);
    cart.checkout();


    cout << "\n--- Switching to Bitcoin Strategy ---" << endl;

    auto bitcoinStrategy = make_shared<BitcoinPayment>("1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa");
    cart.setPaymentMethod(bitcoinStrategy);
    cart.addAmount(500); // Total cart = $500
    cart.checkout();


    return 0;
}