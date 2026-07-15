

#include <iostream>
#include <string>

using namespace std;

// 4. Builder Design Pattern
// separate the construction of complex object from its representation so that the same construction process can create different representations.


// consequences of using the Builder Design Pattern:
// 1. Separation of Construction and Representation: The Builder pattern separates the construction of a complex object from its representation, allowing the same construction process to create different representations. This promotes flexibility and reusability.
// 2. Encapsulation of Construction Logic: The pattern encapsulates the construction logic within the builder classes, making it easier to manage and modify the construction process without affecting the client code.
// 3. Fluent Interface: The Builder pattern often provides a fluent interface, allowing clients to chain method calls for building the object step by step. This can lead to more readable and expressive code.
// 4. Complexity Management: The Builder pattern is particularly useful when constructing complex objects with many optional parameters or configurations. It helps manage complexity by providing a clear and structured way to build the object.
// 5. Potential for Overhead: The Builder pattern can introduce additional overhead in terms of code complexity and the number of classes involved. It may not be necessary for simple objects, and its use should be justified based on the complexity of the object being constructed.


// components of the Builder Design Pattern:
// 1. Product: Represents the complex object being constructed. It can have multiple representations or variations.
// 2. Builder Interface: Defines the methods for creating the different parts of the product.
// 3. Concrete Builders: Implement the builder interface and provide specific implementations for constructing the product's parts. Each concrete builder can create a different representation of the product.
// 4. Director: Controls the construction process by using a builder object. It defines the order in which to call the builder's methods to create the product.
// 5. Client: Creates a director object and configures it with a specific builder. The client then initiates the construction process through the director, which uses the builder to create the desired product representation.

// example use case for builder design pattern:
// 1. Complex Object Construction: When constructing complex objects with many optional parameters or configurations, the Builder pattern can provide a clear and structured way to build the object step by step.
// 2. Document Generation: In applications that generate documents (e.g., reports, invoices), the Builder pattern can be used to create different document formats (PDF, HTML, etc.) using the same construction process.
// 3. Game Character Creation: In video games, the Builder pattern can be used to create different types of game characters (e.g., warriors, mages) with various attributes and equipment using the same construction process.

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