#include <iostream>
#include <memory>
#include <vector>
#include <string>

// Command Design Pattern
// Intent: Encapsulate a request as an object, thereby allowing for parameterization of clients with queues, requests, and operations, and support undoable operations.

// Example use case for command design pattern:
// 1. GUI Buttons: In a graphical user interface, buttons can be associated with commands that encapsulate the action to be performed when the button is clicked. This allows for easy customization and reusability of button actions.
// 2. Macro Recording: In applications that support macro recording, user actions can be encapsulated as command objects, allowing for the recording and playback of sequences of actions.
// 3. Undo/Redo Functionality: In text editors or drawing applications, commands can be used to implement undo and redo functionality by storing executed commands in a history stack.


// Consequences of using the Command Design Pattern:
// 1. Decoupling: The pattern decouples the object that invokes the operation from the one that knows how to perform it, promoting flexibility and reusability.
// 2. Extensibility: New commands can be added without changing existing code, making it easy to extend the system with new functionality.
// 3. Support for Undo/Redo: The pattern naturally supports undo and redo operations by maintaining a history of executed commands.
// 4. Macro Commands: The pattern allows for the creation of composite commands (macros) that can execute a sequence of commands, enabling complex operations to be treated as a single command.

// Components of the Command Design Pattern:
// 1. Command Interface: Declares an interface for executing an operation.
// 2. Concrete Commands: Implement the command interface and define the binding between a Receiver and an action.
// 3. Receiver: Knows how to perform the operations associated with carrying out a request. Any class can serve as a Receiver.
// 4. Invoker: Asks the command to carry out the request. It can store commands and execute them at a later time.
// 5. Client: Creates a ConcreteCommand object and sets its receiver. The client is responsible for configuring the command objects and associating them with the appropriate receivers and invokers.


// --- The Receiver ---
// This is the object that actually knows how to perform the real work.
class Light {
public:
    void turnOn() {
        std::cout << "The light is ON\n";
    }
    void turnOff() {
        std::cout << "The light is OFF\n";
    }
};

// --- The Command Interface ---
// All concrete commands will implement this execute (and optionally undo) method.
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

// --- Concrete Commands ---
// These bind a Receiver (the Light) to specific actions (turnOn / turnOff).
class LightOnCommand : public Command {
private:
    std::shared_ptr<Light> m_light;
public:
    LightOnCommand(std::shared_ptr<Light> light) : m_light(light) {}

    void execute() override {
        m_light->turnOn();
    }
    void undo() override {
        m_light->turnOff(); // The opposite of turning it on
    }
};

class LightOffCommand : public Command {
private:
    std::shared_ptr<Light> m_light;
public:
    LightOffCommand(std::shared_ptr<Light> light) : m_light(light) {}

    void execute() override {
        m_light->turnOff();
    }
    void undo() override {
        m_light->turnOn(); // The opposite of turning it off
    }
};

// --- The Invoker ---
// This handles the commands, triggers their execution, and tracks history for undos.
class RemoteControl {
private:
    std::shared_ptr<Command> m_slot;
    std::vector<std::shared_ptr<Command>> m_history; // Stack to track actions for undo
public:
    void setCommand(std::shared_ptr<Command> command) {
        m_slot = command;
    }

    void pressButton() {
        if (m_slot) {
            m_slot->execute();
            m_history.push_back(m_slot); // Save to history
        }
    }

    void pressUndo() {
        if (!m_history.empty()) {
            std::cout << "Undoing last action... ";
            m_history.back()->undo();
            m_history.pop_back();
        } else {
            std::cout << "Nothing to undo.\n";
        }
    }
};

// --- The Client ---
int main() {
    // 1. Create the receiver
    auto livingRoomLight = std::make_shared<Light>();

    // 2. Create the commands and pass the receiver to them
    auto lightOn = std::make_shared<LightOnCommand>(livingRoomLight);
    auto lightOff = std::make_shared<LightOffCommand>(livingRoomLight);

    // 3. Create the invoker
    RemoteControl remote;

    // Turn the light on
    remote.setCommand(lightOn);
    remote.pressButton();

    // Turn the light off
    remote.setCommand(lightOff);
    remote.pressButton();

    // Undo actions
    remote.pressUndo(); // Should turn the light back ON
    remote.pressUndo(); // Should turn the light back OFF

    return 0;
}


