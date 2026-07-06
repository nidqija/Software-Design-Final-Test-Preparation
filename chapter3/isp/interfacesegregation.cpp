#include <iostream>

using namespace std;


// 3. Interface Segregation Principle (ISP)
// the code should not force clients to depend on interfaces they do not use


// benefit of ISP
// 1. Reduced Complexity: Clients only need to know about the methods they actually use, which simplifies the interface and reduces cognitive load.
// 2. Increased Flexibility: Clients can implement only the interfaces they need, allowing for more flexible and modular designs.
// 3. Improved Maintainability: Changes to one interface do not affect clients that do not use it, making the system easier to maintain and evolve.


// disadvatages of ISP
// 1. Increased Number of Interfaces: Following ISP can lead to a proliferation of interfaces, which may increase the complexity of the system and make it harder to navigate.
// 2. Potential for Inconsistent Design: If not carefully managed, the creation of multiple interfaces can lead to inconsistencies in design and naming conventions.
// 3. Overhead in Implementation: Implementing multiple interfaces may require additional boilerplate code, which can increase development time and effort.

// ========================= Lists of Interfaces for Segregation ================================ //

class IPrinter {
    
    public:
        virtual void printReceipt() = 0; // Pure virtual function for printing receipts

};


class IReceiptGenerator {
    
    public:
        virtual void generateReceipt() = 0; // Pure virtual function for generating receipts
};


class IPaymentProcessor {
    
    public:
        virtual void processPayment() = 0; // Pure virtual function for processing payments
};


// =======================================================================================================



// ========================== Concrete Implementations of Segregated Interfaces ======================================== //


//  credit card payment class implements both IPrinter and IPaymentProcessor interfaces only

class CreditCardPayment : public IPrinter, public IPaymentProcessor {

    private:
        double amount;
    
    public:
        CreditCardPayment(double amount = 0.0) : amount(amount) {}
        void printReceipt() override {
            cout << "Printing credit card receipt" << endl;
        }

        void processPayment() override {
            cout << "Processing credit card payment of $" << amount << endl;
        }
};


// QR payment class implements both IReceiptGenerator and IPaymentProcessor interfaces only 

class QRPayment : public IReceiptGenerator, public IPaymentProcessor {
    
    private:
        double amount;


    public:


        QRPayment(double amount = 0.0) : amount(amount) {}
        void generateReceipt() override {
            cout << "Generating QR receipt for $" << amount << endl;
        }

        void processPayment() override {
            cout << "Processing QR payment of $" << amount << endl;
        }
};


int main(){
    
    CreditCardPayment creditCardPayment(100.0);
    creditCardPayment.processPayment();
    creditCardPayment.printReceipt();

    QRPayment qrPayment(200.0);
    qrPayment.processPayment();
    qrPayment.generateReceipt();

    return 0;
}


