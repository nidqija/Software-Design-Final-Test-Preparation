#include <iostream>
#include <string>

using namespace std;

// 2. Modularity
// Modularity is the design principle that breaks a program into separate, independent modules
// Each module encapsulates a specific functionality and can be developed, tested, and maintained independently
// the advantages of modularity include easier to solve complex problems, improved code organization, and enhanced maintainability


class Engine {
public:
    void start() {
        cout << "Engine starting...\n";
    }

    void stop() {
        cout << "Engine stopping...\n";
    }
};

// --- CONTINUING CODEBASE ---

// Independent Module 2: Handles entertainment only.
// It doesn't care how the engine works or if the car is even moving.
class Stereo {
public:
    void playMusic(string song) {
        cout << "Stereo playing: '" << song << "' 🎵\n";
    }

    void turnOff() {
        cout << "Stereo turning off.\n";
    }
};

// Independent Module 3: The Orchestrator (The Car)
// It brings the independent modules together using "Composition".
class Car {
private:
    // We plug our independent bricks right into the car
    Engine engine; 
    Stereo stereo;
    string model;

public:
    Car(string carModel) : model(carModel) {}

    // This function coordinates our modules to create a "start trip" feature
    void startTrip(string favoriteSong) {
        cout << "=== Getting into my " << model << " ===\n";
        engine.start();                 // Using the Engine module
        stereo.playMusic(favoriteSong); // Using the Stereo module
        cout << "Ready to drive!\n\n";
    }

    void endTrip() {
        cout << "=== Arrived at destination ===\n";
        stereo.turnOff();
        engine.stop();
        cout << "Goodbye!\n\n";
    }
};

int main() {
    // Because of modularity, creating and running a complex object like a Car 
    // becomes incredibly clean and simple in our main application logic.
    Car myCar("Electric Sedan");

    myCar.startTrip("Highway Star");
    myCar.endTrip();

    return 0;
}