#include <iostream>
#include <string>
#include <memory>

using namespace std;



// Chain of Responsibility Design Pattern
// Intent: Avoid coupling the sender of a request to its receiver by giving more than one object a chance to handle the request.
// The request is passed along a chain of potential handlers until one of them handles it.


// Example use case for chain of responsibility design pattern:
// 1. Customer Support System: In a customer support system, requests can be routed through different levels of support (e.g., Level 1, Level 2, Level 3) based on the complexity of the issue. Each level can decide whether to handle the request or pass it to the next level.
// 2. Logging Framework: A logging framework can use the Chain of Responsibility pattern to allow multiple loggers (e.g., console logger, file logger, remote logger) to process log messages. Each logger can decide whether to handle the message or pass it along the chain.
// 3. Event Handling in GUI: In a graphical user interface (GUI), events (like mouse clicks or key presses) can be passed through a chain of event handlers. Each handler can choose to process the event or pass it to the next handler in the chain.

// Consequences of using the Chain of Responsibility Design Pattern:
// 1. Decoupling: The pattern decouples the sender of a request from its receivers, allowing for more flexible and maintainable code.   
// 2. Dynamic Handling: Handlers can be added or removed at runtime, enabling dynamic changes to the chain of responsibility.
// 3. Responsibility Sharing: Multiple handlers can share the responsibility of processing requests, allowing for more complex and nuanced handling logic.
// 4. Potential for Unhandled Requests: If no handler in the chain can process a request, it may go unhandled, which could lead to unexpected behavior if not properly managed.

// Components of the Chain of Responsibility Design Pattern:
// 1. Handler Interface: Defines a method for handling requests and an optional link to the next handler in the chain.
// 2. Concrete Handlers: Implement the handler interface and decide whether to process the request
// or pass it to the next handler in the chain.
// 3. Client: Initiates the request and sends it to the first handler in the chain, without needing to know which handler will ultimately process it.

// The types of issues that can occur
enum class Priority {
    LOW,
    MEDIUM,
    HIGH,
    CRITICAL
};

// ==========================================
// 1. Base Handler Interface
// ==========================================
class SupportHandler {
protected:
    shared_ptr<SupportHandler> nextHandler; // Link to the next object in the chain

public:
    virtual ~SupportHandler() = default;

    // Sets the next link in the chain
    void setNext(shared_ptr<SupportHandler> next) {
        this->nextHandler = next;
    }

    // The core template method for passing requests down the chain
    virtual void handleRequest(Priority priority, const string& message) {
        if (nextHandler) {
            nextHandler->handleRequest(priority, message);
        } else {
            cout << "Chain End: No handler found for request: \"" << message << "\"\n";
        }
    }
};


// ==========================================
// 2. Concrete Handlers
// ==========================================

// Level 1: Basic Support (Handles LOW priority)
class Level1Support : public SupportHandler {
public:
    void handleRequest(Priority priority, const string& message) override {
        if (priority == Priority::LOW) {
            cout << "[Level 1 Support] Handled basic request: \"" << message << "\"\n";
        } else {
            cout << "[Level 1 Support] Cannot handle. Escalating...\n";
            SupportHandler::handleRequest(priority, message); // Forwarding
        }
    }
};

// Level 2: Technical Support (Handles MEDIUM priority)
class Level2Support : public SupportHandler {
public:
    void handleRequest(Priority priority, const string& message) override {
        if (priority == Priority::MEDIUM) {
            cout << "[Level 2 Tech Support] Handled medium request: \"" << message << "\"\n";
        } else {
            cout << "[Level 2 Tech Support] Cannot handle. Escalating...\n";
            SupportHandler::handleRequest(priority, message); // Forwarding
        }
    }
};

// Level 3: Engineering Team (Handles HIGH priority)
class Level3Support : public SupportHandler {
public:
    void handleRequest(Priority priority, const string& message) override {
        if (priority == Priority::HIGH) {
            cout << "[Level 3 Engineering] Handled critical request: \"" << message << "\"\n";
        } else {
            SupportHandler::handleRequest(priority, message); // Forwarding
        }
    }
};

class Level4Support : public SupportHandler {
public:
    void handleRequest(Priority priority, const string& message) override {
        if(priority == Priority::CRITICAL) {
            cout << "[Level 4 Support] Handled CRITICAL request: \"" << message << "\"\n";
        } else {
            SupportHandler::handleRequest(priority, message); // Forwarding
        }
    }

};


// ==========================================
// Client Code
// ==========================================
int main() {
    // 1. Instantiate the handlers
    auto level1 = make_shared<Level1Support>();
    auto level2 = make_shared<Level2Support>();
    auto level3 = make_shared<Level3Support>();
    auto level4 = make_shared<Level4Support>();
    // 2. Chain them together: Level 1 -> Level 2 -> Level 3
    level1->setNext(level2);
    level2->setNext(level3);
    level3->setNext(level4); // Level 4 is the final handler

    // 3. Send diverse requests to the entry point (Level 1)
    cout << "--- Sending Request A ---" << endl;
    level1->handleRequest(Priority::LOW, "How do I change my password?");

    cout << "\n--- Sending Request B ---" << endl;
    level1->handleRequest(Priority::MEDIUM, "The payment gateway is throwing a timeout error.");

    cout << "\n--- Sending Request C ---" << endl;
    level1->handleRequest(Priority::HIGH, "DATABASE IS DOWN! MISSION CRITICAL ERROR!");

    cout << "\n--- Sending Request D ---" << endl;
    level1->handleRequest(Priority::CRITICAL, "System is completely unresponsive!");



    return 0;
}