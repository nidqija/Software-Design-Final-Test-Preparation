


/*#include <iostream>

// Low-level module
class LightBulb {
public:
    void turnOn() { std::cout << "LightBulb: Bulb on..." << std::endl; }
    void turnOff() { std::cout << "LightBulb: Bulb off..." << std::endl; }
};

// High-level module
class Switch {
private:
    LightBulb bulb; // Direct dependency on a concrete class
    bool isOn = false;

public:
    void operate() {
        if (isOn) {
            bulb.turnOff();
            isOn = false;
        } else {
            bulb.turnOn();
            isOn = true;
        }
    }
};*/

#include <iostream>
#include <vector>

// 1. The Abstraction (Interface)
// Both high-level and low-level modules depend on this.
class ISwitchable {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual ~ISwitchable() {}
};

// 2. Low-level Modules (Concrete implementations)
class LightBulb : public ISwitchable {
public:
    void turnOn() override { std::cout << "LightBulb: Glowing bright!" << std::endl; }
    void turnOff() override { std::cout << "LightBulb: Dark now." << std::endl; }
};

class Fan : public ISwitchable {
public:
    void turnOn() override { std::cout << "Fan: Spinning fast!" << std::endl; }
    void turnOff() override { std::cout << "Fan: Stopping." << std::endl; }
};


class Switch {
    private:
        ISwitchable* device; // Dependency on the abstraction, not the concrete class
        bool isOn = false;


    public:
        Switch(ISwitchable* device) : device(device) {}

        void operate() {
            if (isOn) {
                device->turnOff();
                isOn = false;
            } else {
                device->turnOn();
                isOn = true;
            }
        }
};


int main(){
    
    LightBulb bulb;
    Fan fan;

    Switch lightSwitch(&bulb);
    Switch fanSwitch(&fan);

    lightSwitch.operate(); // Turns on the light
    fanSwitch.operate();   // Turns on the fan

    lightSwitch.operate(); // Turns off the light
    fanSwitch.operate();   // Turns off the fan

    return 0;
}