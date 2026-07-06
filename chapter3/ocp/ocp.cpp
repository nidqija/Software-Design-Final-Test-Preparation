#include <iostream>

using namespace std;

// 2. Open/Closed Principle (OCP)
// the code must be open for extension but closed for modification





// benefit of OCP
// 1. Extensibility: New functionality can be added without modifying existing code, reducing the risk of introducing bugs.
// 2. Maintainability: Changes to existing code are minimized, making it easier to maintain and understand.
// 3. Reusability: Components can be reused in different contexts without modification, promoting code reuse and reducing duplication.



// disadvantages of OCP
// 1. Complexity: Designing a system that adheres to OCP can introduce additional complexity, especially when creating abstract classes and interfaces.
// 2. Overhead: The use of polymorphism and abstraction can introduce runtime overhead, which may impact performance in certain scenarios.
// 3. Learning Curve: Developers may need to understand design patterns and principles to effectively implement OCP, which can increase the learning curve for new team members.



// abstract class representing a payment method
class PaymentMethod {


    public:
        // pure virtual function to process payment, must be implemented by derived classes
        virtual void processPayment(double amount) = 0; // Pure virtual function



    virtual ~PaymentMethod() {
            cout << "PaymentMethod object destroyed." << endl;
        }

    
};



// concrete class for credit card payment
class CreditCardPayment : public PaymentMethod {
    public:
        // override the pure virtual function to provide specific implementation for credit card payment
        void processPayment(double amount) override {
            cout << "Processing credit card payment of $" << amount << endl;
        }


    // destructor to clean up resources if needed
    ~CreditCardPayment() {
            cout << "CreditCardPayment object destroyed." << endl;
        }
};


// concrete class for PayPal payment
class PayPalPayment : public PaymentMethod {
    public:
        // override the pure virtual function to provide specific implementation for PayPal payment
        void processPayment(double amount) override {
            cout << "Processing PayPal payment of $" << amount << endl;
        }

    // destructor to clean up resources if needed
    ~PayPalPayment() {
            cout << "PayPalPayment object destroyed." << endl;
        }
};




// client code demonstrating the Open/Closed Principle
int main(){
    
    PaymentMethod* payment1 = new CreditCardPayment();
    payment1->processPayment(100.0);
    delete payment1; // Clean up memory to avoid memory leak

    PaymentMethod* payment2 = new PayPalPayment();
    payment2->processPayment(200.0);
    delete payment2; // Clean up memory to avoid memory leak

    return 0;
}




