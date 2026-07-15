#include <iostream>
#include <memory>
#include <string>

using namespace std;



// Decorator Pattern Example
// 1. attach additional responsibilites to an object dynamically
// 2. provide a flexible alternative to subclassing for extending functionality
// 3. allows behavior to be added to individual objects, without affecting the behavior of other objects from the same class


// Motivation
// 1. if we want to add new responsibilities to an object , we can create a new subclass that extends the original class and adds the new behavior , not to the original class itself
// 2. it is a flexible way to add behavior to an object without modifying its code or creating a new subclass for every possible combination of behaviors



// Components in decorator pattern
// 1. Component: defines the interface for objects that can have responsibilities added to them dynamically
// 2. Concrete Component: the actual object we want to decorate later
// 3. Decorator: maintains a reference to a Component object and defines an interface that conforms to Component's interface
// 4. Concrete Decorators: add responsibilities to the component dynamically 
// 5. Client: creates a Concrete Component object and wraps it with one or more Decorator objects



// ==========================================
// 1. Component Interface
// ==========================================
// Defines the interface for objects that can have responsibilities 
// added to them dynamically.
class Beverage {
public:
    virtual ~Beverage() = default;
    virtual string getDescription() const = 0;
    virtual double cost() const = 0;
};

// ==========================================
// 2. Concrete Component
// ==========================================
// The actual object we want to decorate later.
class Espresso : public Beverage {
public:
    string getDescription() const override {
        return "Espresso";
    }
    double cost() const override {
        return 2.00;
    }
};

// ==========================================
// 3. Decorator Base Class
// ==========================================
// It maintains a reference to a Component object and defines an 
// interface that conforms to Component's interface.
class CondimentDecorator : public Beverage {
protected:
    unique_ptr<Beverage> beverage; // Wrapping the component

public:
    CondimentDecorator(unique_ptr<Beverage> bev) : beverage(move(bev)) {}
};

// ==========================================
// 4. Concrete Decorators
// ==========================================
// Decorator A: Adds Milk
class Milk : public CondimentDecorator {
public:
    Milk(unique_ptr<Beverage> bev) : CondimentDecorator(move(bev)) {}

    string getDescription() const override {
        return beverage->getDescription() + ", Milk";
    }

    double cost() const override {
        return beverage->cost() + 0.50; // Adds its own cost to the base cost
    }
};

// Decorator B: Adds Caramel
class Caramel : public CondimentDecorator {
public:
    Caramel(unique_ptr<Beverage> bev) : CondimentDecorator(move(bev)) {}

    string getDescription() const override {
        return beverage->getDescription() + ", Caramel";
    }

    double cost() const override {
        return beverage->cost() + 0.75; // Adds its own cost
    }
};


// if we want to add more decorators, we can create new classes that inherit 
// from CondimentDecorator and implement the getDescription() and cost() methods accordingly. 
// This allows us to create a flexible and extensible system for adding new behaviors 
// to our objects without modifying their existing code.

class WhippedCream : public CondimentDecorator {
public:
    WhippedCream(unique_ptr<Beverage> bev) : CondimentDecorator(move(bev)) {}

    string getDescription() const override {
        return beverage->getDescription() + ", Whipped Cream";
    }

    double cost() const override {
        return beverage->cost() + 0.60; // Adds its own cost
    }
};

// ==========================================
// Execution
// ==========================================
int main() {
    // Step 1: Start with a plain Espresso
    unique_ptr<Beverage> myOrder = make_unique<Espresso>();
    cout << myOrder->getDescription() << " -> $" << myOrder->cost() << endl;

    // Step 2: Decorate it with Milk
    myOrder = make_unique<Milk>(move(myOrder));
    cout << myOrder->getDescription() << " -> $" << myOrder->cost() << endl;

    // Step 3: Decorate it again with Caramel
    myOrder = make_unique<Caramel>(move(myOrder));
    cout << myOrder->getDescription() << " -> $" << myOrder->cost() << endl;

    myOrder = make_unique<WhippedCream>(move(myOrder));
    cout << myOrder->getDescription() << " -> $" << myOrder->cost() << endl;

    return 0;
}