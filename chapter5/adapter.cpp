#include <iostream>
#include <memory>
#include <string>

using namespace std;


// Adapter Pattern 
// 1. Convert interface of a class into another interface that clients expect
// 2. Adapter lets classes work together that couldn't otherwise because of incompatible interfaces


// Consequences of implementing the Adapter Pattern:
// 1. adapts adaptee to the trget by committing to a concrete adaptee class
// 2. a class adaptee wont work when we want to adapt a class and all of its subclasses
// 3. we let a signle adapter  work with many adaptees
// 4. it makes it harder to override adaptee behavior in the adapter class


// ========================================================
// 1. The Target (What the client expects)
// ========================================================
// The system expects all charging cables to use a USB-C interface.
class UsbCChargeable {
public:
    virtual ~UsbCChargeable() = default;
    virtual void chargeWithUsbC() = 0;
};

class UsbBChargeable {
public:
    virtual ~UsbBChargeable() = default;
    virtual void chargeWithUsbB() = 0;
};

// ========================================================
// 2. The Adaptee (The incompatible legacy code)
// ========================================================
// An old device that only charges via a legacy Micro-USB port.
class LegacyMicroUsbDevice {
public:
    void chargeWithMicroUsb() {
        cout << "Charging device slowly using a old Micro-USB cable..." << endl;
    }
};

// ========================================================
// 3. The Adapter (The bridge)
// ========================================================
// It inherits the Target interface, but wraps the Adaptee inside.
class MicroUsbToUsbCAdapter : public UsbCChargeable {
private:
    unique_ptr<LegacyMicroUsbDevice> legacyDevice; // The wrapped object

public:
    MicroUsbToUsbCAdapter(unique_ptr<LegacyMicroUsbDevice> device) 
        : legacyDevice(move(device)) {}

    // When the client tries to use USB-C, translate it to Micro-USB
    void chargeWithUsbC() override {
        cout << "[Adapter] Translating USB-C power signals to Micro-USB..." << endl;
        legacyDevice->chargeWithMicroUsb();
    }
};

class MicroUsbToUsbBAdapter : public UsbBChargeable {
private:
    unique_ptr<LegacyMicroUsbDevice> legacyDevice; // The wrapped object    

public:
    MicroUsbToUsbBAdapter(unique_ptr<LegacyMicroUsbDevice> device) 
        : legacyDevice(move(device)) {}

    // When the client tries to use USB-B, translate it to Micro-USB
    void chargeWithUsbB() override {
        cout << "[Adapter] Translating USB-B power signals to Micro-USB..." << endl;
        legacyDevice->chargeWithMicroUsb();
    }
};

// ========================================================
// 4. The Client
// ========================================================
// This function only knows how to deal with modern USB-C interfaces.
class ModernChargingStation {
public:
    void plugIn(UsbCChargeable* device) {
        cout << "Modern charging station detected a connection." << endl;
        device->chargeWithUsbC();
        
    }

    void plugIn(UsbBChargeable* device) {
        cout << "Modern charging station detected a connection." << endl;
        device->chargeWithUsbB();
    }
};

// ========================================================
// Execution
// ========================================================
int main() {
    ModernChargingStation station;

    // We have an old legacy device
    auto oldPhone = make_unique<LegacyMicroUsbDevice>();
    auto oldTablet = make_unique<LegacyMicroUsbDevice>();

    // station.plugIn(oldPhone.get()); 
    // ^ ERROR: Compiler won't allow this! Interfaces don't match.

    // Solution: Wrap the old device inside our adapter
    auto adapter = make_unique<MicroUsbToUsbCAdapter>(move(oldPhone));
    auto adapter2 = make_unique<MicroUsbToUsbBAdapter>(move(oldTablet));


    // Now the station can perfectly interact with it!
    station.plugIn(adapter.get());
    station.plugIn(adapter2.get());

    return 0;
}