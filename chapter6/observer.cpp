#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>



// Observer Design Pattern
// Intent: Define a one-to-many dependency between objects so that when one object changes state, all its dependents are notified and updated automatically.



// other example use case for observer design pattern:
// 1. Stock Market Notifier: A stock market application can use the Observer pattern to notify multiple clients (observers) about changes in stock prices. When a stock price changes, all registered clients receive updates in real-time.
// 2. Social Media Notifications
// 3. Chat Applications ( notification of new messages)


// Consequences of using the Observer Design Pattern:
// 1. Loose Coupling: The Observer pattern promotes loose coupling between the subject and its observers. The subject doesn't need to know the concrete classes of its observers, allowing for greater flexibility and easier maintenance.
// 2. Dynamic Relationships: Observers can be added or removed at runtime, enabling dynamic relationships between objects. This is particularly useful in scenarios where the number of observers may change over time.
// 3. Broadcast Communication: The pattern allows for broadcast communication, where a single change in the subject can notify multiple observers simultaneously. This is efficient and reduces the need for direct communication between objects.
// 4. Potential Performance Overhead: If there are many observers or frequent updates, the notification process can introduce performance overhead. Careful consideration is needed to manage the number of observers and the frequency of updates.


// Components of the Observer Design Pattern:
// 1. Observer Interface: Defines the update method that observers must implement to receive notifications.
// 2. Concrete Observers: Implement the Observer interface and define how they respond to updates from the subject. It maintains a reference to the subject to access its state if needed.
// 3. Subject Interface: Defines methods for attaching, detaching, and notifying observers.
// 4. Concrete Subject: Implements the Subject interface and maintains a list of observers. It notifies them of state changes.
// 5. Client: Configures the subject and observers, establishing the relationships between them.
// 6. Collaborations: The subject and observers collaborate to ensure that changes in the subject's state are communicated to all interested observers.



// Terms in the context of this example:
// 1. Push Model: In the push model, the subject actively sends updates to its observers whenever its state changes. 
// Observers receive the new data directly from the subject without requesting it. 
// This model is efficient for scenarios where updates are frequent and observers need to be informed immediately.

using namespace std;

// ==========================================
// 1. Observer Interface (The Subscriber)
// ==========================================
class Observer {
public:
    virtual void update(float temperature, float humidity) = 0;
    virtual ~Observer() = default;
};


// ==========================================
// 2. Subject Interface (The Publisher)
// ==========================================
class Subject {
public:
    virtual void registerObserver(shared_ptr<Observer> o) = 0;
    virtual void removeObserver(shared_ptr<Observer> o) = 0;
    virtual void notifyObservers() = 0;
    virtual ~Subject() = default;
};


// ==========================================
// 3. Concrete Subject
// ==========================================
class WeatherStation : public Subject {
private:
    vector<shared_ptr<Observer>> observers; // List of subscribers
    float temperature;
    float humidity;

public:
    void registerObserver(shared_ptr<Observer> o) override {
        observers.push_back(o);
    }

    void removeObserver(shared_ptr<Observer> o) override {
        // Find and remove the observer from the list
        observers.erase(remove(observers.begin(), observers.end(), o), observers.end());
    }

    void notifyObservers() override {
        for (const auto& observer : observers) {
            observer->update(temperature, humidity);
        }
    }

    // Setters that trigger the notification automatically
    void setMeasurements(float temp, float hum) {
        this->temperature = temp;
        this->humidity = hum;
        cout << "\nWeatherStation: Measurements updated! Temperature: " 
             << temp << "C, Humidity: " << hum << "%" << endl;
        notifyObservers(); // Broadcast the update
    }
};


// ==========================================
// 4. Concrete Observers
// ==========================================
class PhoneDisplay : public Observer {
private:
    string deviceName;
public:
    PhoneDisplay(string name) : deviceName(name) {}

    void update(float temperature, float humidity) override {
        cout << "[" << deviceName << "] Displaying -> Temp: " 
             << temperature << "C, Humidity: " << humidity << "%" << endl;
    }
};

class LoggerDisplay : public Observer {
public:
    void update(float temperature, float humidity) override {
        cout << "[System Log] Saved to database -> " << temperature << "C | " << humidity << "%" << endl;
    }
};


// ==========================================
// Client Code
// ==========================================
int main() {
    // 1. Create the Weather Station (Subject)
    auto station = make_shared<WeatherStation>();

    // 2. Create Displays (Observers)
    auto phone = make_shared<PhoneDisplay>("iPhone 15");
    auto tablet = make_shared<PhoneDisplay>("iPad Pro");
    auto logger = make_shared<LoggerDisplay>();

    // 3. Register subscribers
    station->registerObserver(phone);
    station->registerObserver(tablet);
    station->registerObserver(logger);

    // 4. Simulate weather updates
    station->setMeasurements(24.5f, 65.0f);
    station->setMeasurements(26.2f, 60.0f);

    // 5. Unsubscribe one device and update again
    cout << "\n--- iPhone unsubscribed ---" << endl;
    station->removeObserver(phone);

    station->setMeasurements(22.0f, 75.0f);

    return 0;
}