
// 6. Liskov Substitution Principle (LSP)
// derived classes must be subsitutable for their base classes without altering the correctness of the program



// benefits of LSP
// 1. Code Reusability: LSP allows for the creation of more generic and reusable code. Functions and methods can operate on base class types, and any derived class can be used without modification.
// 2. Maintainability: Code that adheres to LSP is easier to maintain and extend, as changes to base classes do not break derived classes.
// 3. Polymorphism: LSP enables polymorphic behavior, allowing objects of different derived classes to be treated uniformly through base class interfaces, enhancing flexibility and scalability in software design.

// disadvantages of LSP
// 1. Complexity in Design: Ensuring that derived classes adhere to the behavior of their base classes can introduce complexity in the design phase, requiring careful planning and understanding of class hierarchies.
// 2. Runtime Overhead: Implementing LSP may introduce slight runtime overhead due to the additional checks and indirection required for polymorphic behavior.
// 3. Testing Challenges: Testing code that adheres to LSP can be more complex, as it requires ensuring that all derived classes correctly implement the base class interface.




#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

// ==========================================
// BASE CLASS
// ==========================================
class Bird {
public:
    virtual void fly() const {
        cout << "Flapping wings and soaring into the sky!" << endl;
    }

    virtual ~Bird() = default;
};




// ==========================================
// DERIVED CLASSES
// ==========================================
class Sparrow : public Bird {
public:
    void fly() const override {
        cout << "Sparrow flapping wings and soaring into the sky!" << endl;
    }

    ~Sparrow() {
        cout << "Sparrow object destroyed." << endl;
    }
};

class Ostrich : public Bird {
public:
    // CRITICAL LSP VIOLATION: An ostrich cannot fly!
    // We are forced to change the behavior of the base class method 
    // by throwing an exception, breaking the base class's behavioral contract.
    void fly() const override {
        throw runtime_error("Error: Ostriches cannot fly! We just crashed the system.");
    }

    ~Ostrich() {
        cout << "Ostrich object destroyed." << endl;
    }
};

// ==========================================
// CLIENT CODE (Expects any Bird to work)
// ==========================================
void letAllBirdsFly(const vector<Bird*>& aviary) {
    for (const auto& bird : aviary) {
        // The developer trusts the 'Bird' interface promise that .fly() is safe.
        bird->fly(); 
    }
}

int main() {
    vector<Bird*> myAviary;
    myAviary.push_back(new Sparrow());
    
    // Substituting Bird with an Ostrich...
    myAviary.push_back(new Ostrich()); 

    cout << "--- Starting Flight Simulation ---" << endl;
    
    try {
        letAllBirdsFly(myAviary);
    } catch (const exception& e) {
        cout << "\n[CRASH DETECTED] " << e.what() << endl;
    }

    // Clean up memory
    for (auto bird : myAviary) {
        delete bird;
    }

    return 0;
}