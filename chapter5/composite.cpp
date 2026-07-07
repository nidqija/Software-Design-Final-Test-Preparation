#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;


// composite design pattern
// The Composite Design Pattern allows you to compose objects into tree structures to represent part-whole hierarchies.
// It lets clients treat individual objects and compositions of objects uniformly.
// example: A file system where files and folders can be treated uniformly.

// consequences of using the composite design pattern:
// 1. Simplifies client code: Clients can treat individual objects and compositions uniformly, reducing complexity in the client code.
// 2. Flexibility: New types of components can be added without changing existing code, promoting extensibility.

// bad points of using the composite design pattern:
// 1. Overhead: The pattern can introduce additional overhead due to the need for managing collections of components and the recursive nature of the structure.
// 2. Complexity: The design can become complex, especially when dealing with deep hierarchies or when the number of components grows significantly.

// 1. Component (The base interface)
class FileSystemComponent {
public:
    virtual void display(string indent = "") = 0;
    virtual ~FileSystemComponent() = default; // Virtual destructor for safety
};

// 2. Leaf (Individual object - represents a File)
class File : public FileSystemComponent {
private:
    string name;
public:
    File(string name) : name(name) {}

    void display(string indent) override {
        cout << indent << "- File: " << name << endl;
    }
};

// 3. Composite (Group of objects - represents a Folder)
class Folder : public FileSystemComponent {
private:
    string name;
    vector<shared_ptr<FileSystemComponent>> children; // Can hold both Files and Folders
public:
    Folder(string name) : name(name) {}

    void add(shared_ptr<FileSystemComponent> component) {
        children.push_back(component);
    }

    void display(string indent) override {
        cout << indent << "+ Folder: " << name << endl;
        // Delegate the display logic to children uniformly
        for (const auto& child : children) {
            child->display(indent + "  ");
        }
    }
};

// Client Code
int main() {
    // Create individual files (Leaves)
    auto file1 = make_shared<File>("Main.cpp");
    auto file2 = make_shared<File>("Header.h");
    auto file3 = make_shared<File>("Readme.md");

    // Create folders (Composites)
    auto rootFolder = make_shared<Folder>("ProjectRoot");
    auto srcFolder = make_shared<Folder>("Source");

    // Build the tree structure
    srcFolder->add(file1);
    srcFolder->add(file2);

    rootFolder->add(srcFolder);
    rootFolder->add(file3); // Add file directly to root

    // Treat the entire hierarchy uniformly
    cout << "Displaying entire file system structure:" << endl;
    rootFolder->display("");

    return 0;
}