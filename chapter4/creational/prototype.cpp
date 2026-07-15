// 5. Prototype Design Pattern
// The Prototype Pattern is a creational design pattern that allows cloning objects, even complex ones, without coupling to their specific classes.
// It is particularly useful when the cost of creating a new object is expensive or complicated.
// it takes an existing docs format and makes a copy of it, allowing for quick generation of new documents without starting from scratch.
// we only replace the content of the document, while keeping the header, footer, and margin settings intact.


// example use case for prototype design pattern:
// 1. Document Generation: In applications that generate documents (e.g., reports, invoices), the Prototype pattern can be used to create new documents by cloning existing templates and modifying their content.
// 2. Game Development: In video games, the Prototype pattern can be used to create new game objects (e.g., enemies, power-ups) by cloning existing prototypes and modifying their attributes.
// 3. GUI Component Cloning: In graphical user interfaces, the Prototype pattern can be used to create new UI components (e.g., buttons, panels) by cloning existing components and modifying their properties.
// 4. Object Pooling: In scenarios where object creation is expensive, the Prototype pattern can be used to create a pool of reusable objects by cloning existing prototypes and reusing them instead of creating new instances from scratch.



// consequences of using the Prototype Design Pattern:
// 1. Reduced Object Creation Overhead: The Prototype pattern can reduce the overhead of creating new objects, especially when the creation process is complex or resource-intensive. Cloning existing objects can be more efficient than constructing new ones from scratch.
// 2. Flexibility in Object Creation: The pattern allows for greater flexibility in object creation, as new objects can be created by cloning existing ones and modifying their attributes. This can lead to more dynamic and adaptable systems.
// 3. Decoupling from Concrete Classes: The Prototype pattern decouples the client code from the concrete classes of the objects being cloned. This promotes a more modular and maintainable design, as clients can work with abstract interfaces rather than specific implementations.
// 4. Potential for Object Slicing: When cloning objects, there is a risk of object slicing if the clone method is not properly implemented. This can lead to loss of data or behavior in the cloned object, especially when dealing with inheritance hierarchies.


// components of the Prototype Design Pattern:
// 1. Prototype Interface: Declares a method for cloning itself, typically called clone().
// 2. Concrete Prototypes: Implement the Prototype interface and provide specific implementations for cloning themselves. Each concrete prototype can have its own unique attributes and behaviors.
// 3. Prototype Registry: Maintains a collection of prototype instances and provides a way to retrieve and clone them. It acts as a central repository for managing prototypes.
// 4. Client: Creates new objects by requesting clones from the prototype registry or directly from concrete prototypes. The client can modify the cloned objects as needed without being coupled to their specific classes.

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

using namespace std;

// ==========================================
// 1. THE PROTOTYPE INTERFACE
// ==========================================
class Document {
protected:
    string header;
    string footer;
    int marginSize;

public:
    Document(string h, string f, int m) : header(h), footer(f), marginSize(m) {}
    virtual ~Document() = default;

    // The core Prototype method
    virtual Document* clone() const = 0; 
    
    virtual void displayInfo() const = 0;
    
    // Allows customization after cloning
    virtual void setContent(const string& content) = 0;
};

// ==========================================
// 2. CONCRETE PROTOTYPES
// ==========================================

class CorporateReport : public Document {
private:
    string reportContent;
public:
    CorporateReport(string h, string f, int m) : Document(h, f, m), reportContent("") {}

    // Uses the compiler-generated copy constructor to replicate itself
    Document* clone() const override {
        return new CorporateReport(*this); 
    }

    void setContent(const string& content) override {
        reportContent = content;
    }

    void displayInfo() const override {
        cout << "[Report] Header: " << header << " | Margins: " << marginSize << "mm" << endl;
        cout << "         Body:   " << reportContent << endl;
        cout << "         Footer: " << footer << "\n" << endl;
    }
};

class Invoice : public Document {
private:
    string transactionDetails;
public:
    Invoice(string h, string f, int m) : Document(h, f, m), transactionDetails("") {}

    Document* clone() const override {
        return new Invoice(*this);
    }

    void setContent(const string& content) override {
        transactionDetails = content;
    }

    void displayInfo() const override {
        cout << "[Invoice] Header: " << header << " | Margins: " << marginSize << "mm" << endl;
        cout << "          Billing: " << transactionDetails << endl;
        cout << "          Footer:  " << footer << "\n" << endl;
    }
};

// ==========================================
// 3. PROTOTYPE REGISTRY
// ==========================================
enum TemplateType { CORP_REPORT, CLIENT_INVOICE };

class DocumentRegistry {
private:
    unordered_map<TemplateType, Document*> templates;

public:
    DocumentRegistry() {
        // Complex, expensive setup happens exactly ONCE here (e.g., loading branding layouts)
        templates[CORP_REPORT] = new CorporateReport("Acme Corp Q3 Confidential Header", "Page 1 - Copyright Acme 2026", 25);
        templates[CLIENT_INVOICE] = new Invoice("Acme Corp Invoice Systems", "Thank you for your business. Terms: Net 30", 15);
    }

    ~DocumentRegistry() {
        // FIXED: Traditional range-based loop compatible with all GCC versions
        for (auto const& pair : templates) {
            delete pair.second; // pair.second contains the Document* pointer
        }
    }

    // Instantly returns a lightweight clone of the requested type
    Document* getTemplate(TemplateType type) {
        return templates[type]->clone();
    }
};

// ==========================================
// CLIENT ENGINE
// ==========================================
int main() {
    DocumentRegistry systemRegistry;

    cout << "--- System Initialized: Generating Documents From Pre-baked Templates ---\n" << endl;

    // User A wants a corporate report
    Document* doc1 = systemRegistry.getTemplate(CORP_REPORT);
    doc1->setContent("Financial numbers look excellent this quarter, up 14%.");
    doc1->displayInfo();

    // User B wants an invoice
    Document* doc2 = systemRegistry.getTemplate(CLIENT_INVOICE);
    doc2->setContent("Item #4002: Cloud Hosting Subscriptions - $1,200.00");
    doc2->displayInfo();

    // User C wants another report (completely isolated from doc1's content modification)
    Document* doc3 = systemRegistry.getTemplate(CORP_REPORT);
    doc3->setContent("HR updates: 5 new engineers joined the team.");
    doc3->displayInfo();

    // Clean up current active instances
    delete doc1;
    delete doc2;
    delete doc3;

    return 0;
}