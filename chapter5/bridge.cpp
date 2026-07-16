#include <iostream>
#include <memory>
#include <string>

using namespace std;

// 1. Bridge Pattern
// The Bridge Pattern is a structural design pattern that decouples an abstraction from its implementation,
// allowing the two to vary independently. It is useful when both the abstractions and their implementations should be extensible by subclassing.

// Consequences for bridge pattern:
// 1. Decouples interface and implementation, allowing them to vary independently.
// 2. Improves extensibility by allowing new abstractions and implementations to be added without modifying existing code.
// 3. Reduces the number of classes by avoiding a combinatorial explosion of classes for every possible combination of abstraction and implementation.
// 4. Promotes the use of composition over inheritance, leading to more flexible designs.


// Component in bridge pattern:
// 1. Abstraction: Defines the abstraction's interface and maintains a reference to an object of type Implementor.
// 2. Refined Abstraction: Extends the interface defined by Abstraction.
// 3. Implementor: Defines the interface for implementation classes. This interface doesn't have to correspond exactly to Abstraction's interface; in fact, the two interfaces can be quite different. Typically, the Implementor interface provides only primitive operations, and Abstraction defines higher-level operations based on these primitives.
// 4. Concrete Implementor: Implements the Implementor interface and defines its concrete implementation.


// ==========================================
// 1. Implementation Interface (The Details)
// ==========================================
class Device {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual void setVolume(int volume) = 0;
    virtual ~Device() = default;
};

// Concrete Implementation A
class TV : public Device {
public:
    void turnOn() override { cout << "TV: Power On\n"; }
    void turnOff() override { cout << "TV: Power Off\n"; }
    void setVolume(int volume) override { cout << "TV: Volume set to " << volume << "%\n"; }
};

// Concrete Implementation B
class Radio : public Device {
public:
    void turnOn() override { cout << "Radio: Power On\n"; }
    void turnOff() override { cout << "Radio: Power Off\n"; }
    void setVolume(int volume) override { cout << "Radio: Volume set to " << volume << "%\n"; }
};

class ToyCar : public Device {
public:
    void turnOn() override { cout << "Toy Car: Power On\n"; }
    void turnOff() override { cout << "Toy Car: Power Off\n"; }
    void setVolume(int volume) override { cout << "Toy Car: Volume set to " << volume << "%\n"; }
};


// ==========================================
// 2. Abstraction (The High-Level Interface)
// ==========================================
class RemoteControl {
protected:
    shared_ptr<Device> device; // The "Bridge" to the implementation
public:
    RemoteControl(shared_ptr<Device> dev) : device(dev) {}
    virtual ~RemoteControl() = default;

    // High-level operations that delegate to the implementation
    virtual void togglePower() {
        cout << "Remote: Pressing power button...\n";
        device->turnOn();
    }
    
    virtual void volumeUp() {
        cout << "Remote: Pressing volume up...\n";
        device->setVolume(50);
    }
};

// Refined Abstraction (Adding features without touching the Devices)
class AdvancedRemoteControl : public RemoteControl {
public:
    AdvancedRemoteControl(shared_ptr<Device> dev) : RemoteControl(dev) {}

    void mute() {
        cout << "Advanced Remote: Pressing MUTE button...\n";
        device->setVolume(0);
    }
};

class ToyCarRemoteControl : public RemoteControl {
public:
    ToyCarRemoteControl(shared_ptr<Device> dev) : RemoteControl(dev) {}

    void driveForward() {
        cout << "Toy Car Remote: Driving forward...\n";
    }

    void driveBackward() {
        cout << "Toy Car Remote: Driving backward...\n";
    }
};


// ==========================================
// Client Code
// ==========================================
int main() {
    // 1. Create the concrete devices (Implementations)
    auto tv = make_shared<TV>();
    auto radio = make_shared<Radio>();
    auto toyCar = make_shared<ToyCar>();
    
    

    // 2. Control the TV with a basic remote
    cout << "--- Testing TV with Basic Remote ---" << endl;
    RemoteControl basicRemote(tv);
    basicRemote.togglePower();
    basicRemote.volumeUp();

    cout << "\n--- Testing Radio with Advanced Remote ---" << endl;
    // 3. Control the Radio with an advanced remote
    // Notice how we swap both the remote types and the device types independently!
    AdvancedRemoteControl advRemote(radio);
    advRemote.togglePower();
    advRemote.mute();

    // in this code example , we demonstrate the Bridge Design Pattern by decoupling the abstraction (RemoteControl) from its implementation (Device). 
    // This allows us to mix and match different remotes with different devices without modifying their code. 
    // The client code shows how we can control a TV, Radio, and Toy Car using both basic and advanced remotes, 
    // showcasing the flexibility of the design.

    // 4. Control the Toy Car with a specialized remote
    cout << "\n--- Testing Toy Car with Toy Car Remote ---" << endl;
    AdvancedRemoteControl toyCarRemote(toyCar);
    toyCarRemote.togglePower();
    toyCarRemote.volumeUp();


    // 5. Control the Toy Car with a basic remote
    cout << "\n--- Testing Toy Car with Basic Remote ---" << endl;
    RemoteControl toyCarBasicRemote(toyCar);
    toyCarBasicRemote.togglePower();




    return 0;
}