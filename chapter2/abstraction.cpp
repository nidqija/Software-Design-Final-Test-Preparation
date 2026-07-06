#include <iostream>
#include <string>

using namespace std;

// 1. Abstraction
// Abstraction is the process of hiding the implementation details and showing only the functionality to the user
// In C++, abstraction can be achieved using abstract classes and interfaces

// --- THE ABSTRACT INTERFACE ---
// The user only needs to know *what* a Vehicle can do, not *how* it does it.
class Vehicle {
public:
    // Pure virtual functions define the abstract interface
    virtual void startEngine() = 0;
    virtual void accelerate() = 0;
    
    // Virtual destructor ensures proper cleanup of derived objects
    virtual ~Vehicle() {}
};

// --- HIDDEN IMPLEMENTATION DETAILS ---
// Concrete class 1: A traditional gasoline car
class CombustionCar : public Vehicle {
private:
    // These details are completely hidden (abstracted away) from the user
    void injectFuel() { cout << "[Internal] Injecting gasoline into cylinders...\n"; }
    void igniteSparkPlugs() { cout << "[Internal] Spark plugs firing...\n"; }

public:
    void startEngine() override {
        cout << "\nStarting Combustion Car:\n";
        injectFuel();
        igniteSparkPlugs();
        cout << "Result: Engine is idling smoothly. (Vroom!)\n";
    }

    void accelerate() override {
        cout << "Combustion Car accelerating: Fuel flow increased, transmission shifting gears.\n";
    }
};

// Concrete class 2: An electric car
class ElectricCar : public Vehicle {
private:
    // Entirely different hidden mechanics compared to the gas car
    void engageInverter() { cout << "[Internal] Directing DC battery power to AC inverter...\n"; }
    void initializeCooling() { cout << "[Internal] Battery thermal management system active...\n"; }

public:
    void startEngine() override {
        cout << "\nStarting Electric Car:\n";
        engageInverter();
        initializeCooling();
        cout << "Result: Dashboard lights up. System ready. (Silent)\n";
    }

    void accelerate() override {
        cout << "Electric Car accelerating: Instant torque applied to electric motors.\n";
    }
};

// --- THE USER EXPERIENCE ---
// This function doesn't care if the vehicle runs on gas, electricity, or magic.
// It only cares about the abstract functionality.
class Driver {
public:
    void drive(Vehicle& vehicle) {
        // The user interacts ONLY with the high-level functional concepts
        vehicle.startEngine();
        vehicle.accelerate();
    }
};

int main() {
    Driver user;
    
    CombustionCar gasCar;
    ElectricCar tesla;

    cout << "=== Abstraction Demonstration ===\n";

    // The driver uses the exact same interface to control completely different technologies
    user.drive(gasCar);
    user.drive(tesla);

    return 0;
}