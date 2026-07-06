// 5. Prototype Design Pattern
// The Prototype Pattern is a creational design pattern that allows cloning objects, even complex ones, without coupling to their specific classes.
// It is particularly useful when the cost of creating a new object is expensive or complicated.
// it takes an existing docs format and makes a copy of it, allowing for quick generation of new documents without starting from scratch.
// we only replace the content of the document, while keeping the header, footer, and margin settings intact.


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