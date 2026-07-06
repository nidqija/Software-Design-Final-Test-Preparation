

#include <iostream>
#include <string>

using namespace std;

// 4. Builder Design Pattern
// separate the construction of complex object from its representation so that the same construction process can create different representations.




// ==========================================
// 1. PRODUCTS (No shared class hierarchy!)
// ==========================================

// Product A: Created by the Gaming Builder
class GamingRig {
public:
    string cpu, gpu, liquidCooler;
    void showRigSpecs() const {
        cout << "[Gaming Rig] CPU: " << cpu << " | GPU: " << gpu << " | Cooling: " << liquidCooler << endl;
    }
};

// Product B: Created by the Laptop Builder (Completely different class!)
class OfficeLaptop {
public:
    string cpu, batteryLife, screenType;
    void showLaptopSpecs() const {
        cout << "[Office Laptop] CPU: " << cpu << " | Battery: " << batteryLife << " | Screen: " << screenType << endl;
    }
};

// ==========================================
// 2. THE BUILDER INTERFACE
// ==========================================
// Declares construction steps common to all types of builders
class ComputerBuilder {
public:
    virtual void buildCPU() = 0;
    virtual void buildGraphicsOrDisplay() = 0;
    virtual void buildCoolingOrBattery() = 0;
    virtual ~ComputerBuilder() = default;
};

// ==========================================
// 3. CONCRETE BUILDERS (Different implementations)
// ==========================================

class GamingRigBuilder : public ComputerBuilder {
private:
    GamingRig* rig;
public:
    GamingRigBuilder() { rig = new GamingRig(); }
    
    void buildCPU() override { rig->cpu = "AMD Ryzen 9 9950X"; }
    void buildGraphicsOrDisplay() override { rig->gpu = "NVIDIA RTX 5090"; }
    virtual void buildCoolingOrBattery() override { rig->liquidCooler = "360mm AIO Liquid Cooler"; }
    
    // Returns its specific product type
    GamingRig* getResult() { return rig; }
};

class OfficeLaptopBuilder : public ComputerBuilder {
private:
    OfficeLaptop* laptop;
public:
    OfficeLaptopBuilder() { laptop = new OfficeLaptop(); }
    
    void buildCPU() override { laptop->cpu = "Intel Core i5"; }
    void buildGraphicsOrDisplay() override { laptop->screenType = "14-inch IPS Matte Display"; }
    void buildCoolingOrBattery() override { laptop->batteryLife = "15 Hours Lithium-Polymer"; }
    
    // Returns its specific product type
    OfficeLaptop* getResult() { return laptop; }
};

// ==========================================
// 4. THE DIRECTOR CLASS
// ==========================================
// Defines the order in which to call construction steps
class TechnicalDirector {
private:
    ComputerBuilder* builder;
public:
    // Client associates a builder with the director
    void setBuilder(ComputerBuilder* b) {
        builder = b;
    }

    // Controls the recipe/configuration sequence
    void constructMaximumPerformance() {
        builder->buildCPU();
        builder->buildGraphicsOrDisplay();
        builder->buildCoolingOrBattery();
    }
};

// ==========================================
// 5. THE CLIENT
// ==========================================
int main() {
    TechnicalDirector director;

    // Client associates Concrete Builder 1 with the Director
    GamingRigBuilder* gamingBuilder = new GamingRigBuilder();
    director.setBuilder(gamingBuilder);
    
    // Director builds it
    director.constructMaximumPerformance();
    GamingRig* customPC = gamingBuilder->getResult();
    customPC->showRigSpecs();

    cout << "--------------------------------------------------" << endl;

    // Client associates Concrete Builder 2 with the Director
    OfficeLaptopBuilder* laptopBuilder = new OfficeLaptopBuilder();
    director.setBuilder(laptopBuilder);
    
    // Director builds it using the same production configuration steps
    director.constructMaximumPerformance();
    OfficeLaptop* workLaptop = laptopBuilder->getResult();
    workLaptop->showLaptopSpecs();

    // Clean up
    delete gamingBuilder; delete customPC;
    delete laptopBuilder; delete workLaptop;
    return 0;
}