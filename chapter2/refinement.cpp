#include <iostream>
#include <vector>


using namespace std;



// 5. Refinement
// process of elaborating , top down design strategy
// stepwise refinement is a design strategy that involves breaking down a complex problem into smaller, 
// more manageable subproblems. Each subproblem can be solved independently, and 
// the solutions can be combined to form the overall solution. 
// This approach promotes clarity, modularity, and maintainability in software development.


// A simple structure to hold our item data
struct Item {
    string name;
    double price;
};

class CheckoutSystem {
public:
    // ==========================================
    // HIGH-LEVEL STRATEGY (Top-Down Design)
    // ==========================================
    // This is our primary function. It doesn't care about the math details;
    // it just outlines the "big picture" steps to process an order.
    void processOrder(const vector<Item>& cart, double taxRate) {
        double subtotal = calculateSubtotal(cart);
        double tax = calculateTax(subtotal, taxRate);
        double total = calculateTotal(subtotal, tax);
        
        printInvoice(cart, subtotal, tax, total);
    }

private:
    // ==========================================
    // STEPWISE REFINEMENTS (Subproblems)
    // ==========================================
    // Each complex part of the problem is broken down into an independent, 
    // highly cohesive helper function.

    // Refinement 1: How do we sum up the items?
    double calculateSubtotal(const vector<Item>& cart) {
        double sum = 0.0;
        for (const auto& item : cart) {
            sum += item.price;
        }
        return sum;
    }

    // Refinement 2: How do we handle tax calculations?
    double calculateTax(double subtotal, double taxRate) {
        return subtotal * taxRate;
    }

    // Refinement 3: How do we combine subtotal and tax?
    double calculateTotal(double subtotal, double tax) {
        return subtotal + tax;
    }

    // Refinement 4: How do we present the output to the user?
    void printInvoice(const vector<Item>& cart, double subtotal, double tax, double total) {
        cout << "------- INVOICE -------" << endl;
        for (const auto& item : cart) {
            cout << item.name << ": $" << item.price << endl;
        }
        cout << "-----------------------" << endl;
        cout << "Subtotal: $" << subtotal << endl;
        cout << "Tax:      $" << tax << endl;
        cout << "Total:    $" << total << endl;
        cout << "-----------------------" << endl;
    }
};

int main() {
    // Our mock shopping cart
    vector<Item> shoppingCart = {
        {"Laptop Bag", 45.00},
        {"Wireless Mouse", 25.50},
        {"Mechanical Keyboard", 90.00}
    };
    
    double salesTax = 0.08; // 8% tax

    CheckoutSystem checkout;
    
    // We execute the high-level process
    checkout.processOrder(shoppingCart, salesTax);

    return 0;
}