#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;


// 3. Proxy Design Pattern
// 1. provides a surrogate or placeholder for another object to control access to it
// 2. applicable when there is a need for a more versatile or sophisticated reference to an object than a simple pointer


// example of proxy pattern
// 1. remote proxy
// 2. virtual proxy
// 3. protection proxy
// 4. smart reference proxy

// consequences of implementing the proxy pattern
// A remote proxy can hide the factthatthe objectresides in a different address space
// A virtual proxy can perform optimization by creating the object on demand
// Protection proxies and smart references allow additional housekeeping.

// ============================================================================
// 1. The Service Interface 
// "Declares the interface of the Service. The proxy must follow this interface..."
// ============================================================================
class MessageService {
public:
    virtual ~MessageService() = default;
    virtual void sendText(const string& phoneNumber, const string& body) = 0;
};

// ============================================================================
// 2. The Service
// "A class that provides some useful business logic."
// ============================================================================
// This class connects directly to a real network gateway—an expensive operation.
class RealMessageService : public MessageService {
public:
    RealMessageService() {
        cout << "[Service] Establishing connection to GSM/Cellular Gateway network...\n";
    }

    ~RealMessageService() override {
        cout << "[Service] Closing cellular gateway network connection clean.\n";
    }

    void sendText(const string& phoneNumber, const string& body) override {
        cout << "[Service] Routing SMS via cell tower to " << phoneNumber 
             << " | Contents: \"" << body << "\"\n";
    }
};

// ============================================================================
// 3. The Proxy Class
// "Has a reference field that points to a service object. After processing... 
// passes request... Usually, proxies manage the full lifecycle of service objects."
// ============================================================================
class MessageServiceProxy : public MessageService {
private:
    // Reference field to the underlying service
    unique_ptr<RealMessageService> realService; 
    
    // Auxiliary state data for the proxy's own business processing (Rate-limiting logic)
    int tokensLeft = 2; 

public:
    MessageServiceProxy() : realService(nullptr) {
        // "Usually, proxies manage the full lifecycle of their service objects."
        // We defer creation of the expensive RealMessageService here (Lazy Initialization).
        cout << "[Proxy] Proxy instantiated. Real service object lifecycle has NOT started yet.\n";
    }

    ~MessageServiceProxy() override = default; // RAII cleans up realService automatically when Proxy dies

    void sendText(const string& phoneNumber, const string& body) override {
        cout << "[Proxy] Intercepted text request to: " << phoneNumber << "\n";

        // Processing Step A: Access Control / Throttling
        if (tokensLeft <= 0) {
            cout << "[Proxy] !!! ERROR !!! Rate limit exceeded. Text blocked by Proxy.\n";
            return;
        }

        // Processing Step B: Lazy Initialization (Lifecycle management)
        if (!realService) {
            cout << "[Proxy] Lazy Initializing the real service object on-demand.\n";
            realService = make_unique<RealMessageService>();
        }

        // Processing Step C: Forwarding request to service object
        realService->sendText(phoneNumber, body);
        tokensLeft--;
    }
};

// ============================================================================
// 4. The Client
// "Should work with both services and proxies via the same interface."
// ============================================================================
// This client function expects any MessageService interface object. It has no idea 
// if it is holding a proxy layer or a real service layer.
void dispatchSystemAlerts(MessageService& service) {
    service.sendText("+1-555-0199", "Alert: CPU usage spike detected!");
    service.sendText("+1-555-0199", "Alert: Memory usage normalized.");
    service.sendText("+1-555-0199", "Alert: Storage threshold warning!");
}

// ============================================================================
// Execution
// ============================================================================
int main() {
    cout << "=== Client instantiates the Proxy ===\n";
    // Proxy is created, but network gateway is completely asleep
    unique_ptr<MessageService> secureMessagingChannel = make_unique<MessageServiceProxy>();

    cout << "\n=== Client fires events via uniform interface contract ===\n";
    dispatchSystemAlerts(*secureMessagingChannel);

    cout << "\n=== App closing down. Destroying proxy channel... ===\n";
    // Destructor of Proxy drops, which triggers destruction of the Service it manages
    return 0;
}