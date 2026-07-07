#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>



// Flyweight Design Pattern
// allows programs to support a large number of objects efficiently by sharing common parts of 
// state between multiple objects instead of keeping all data in each object.

// Consequences of using the Flyweight Design Pattern:

// 1. Memory Efficiency: The primary benefit of the Flyweight pattern is that it reduces memory usage by sharing common state among multiple objects. 
// This is especially useful when dealing with a large number of similar objects.

// 2. Performance Improvement: By reducing memory consumption, the Flyweight pattern can lead to improved performance,
// especially in scenarios where object creation and destruction are frequent.

// 3. Complexity: Implementing the Flyweight pattern can introduce complexity into the codebase, 
// as it requires careful management of shared state and extrinsic state.


using namespace std;

// ==========================================
// 1. Flyweight (Shared Intrinsic State)
// ==========================================
// This class contains heavy data (texture, mesh, color) that is identical for many objects.
class TreeType {
private:
    string name;
    string color;
    string textureData; // Simulating a heavy image asset
public:
    TreeType(string name, string color, string texture) 
        : name(name), color(color), textureData(texture) {}

    // Extrinsic data (x, y) is passed as arguments to the method
    void draw(int x, int y) {
        cout << "Drawing [" << name << "] (Color: " << color 
             << ") at coordinates (" << x << ", " << y << ")\n";
    }
};


// ==========================================
// 2. Flyweight Factory (Manages Flyweights)
// ==========================================
// Ensures flyweights are shared correctly and never duplicated.
class TreeFactory {
private:
    // Pool of existing unique tree types
    static unordered_map<string, shared_ptr<TreeType>> treeTypes;
public:
    static shared_ptr<TreeType> getTreeType(string name, string color, string texture) {
        string key = name + "_" + color;
        
        // If it doesn't exist in our pool, create a new one
        if (treeTypes.find(key) == treeTypes.end()) {
            cout << ">> Factory: Creating NEW shared TreeType [" << name << "]\n";
            treeTypes[key] = make_shared<TreeType>(name, color, texture);
        } else {
            cout << ">> Factory: Reusing EXISTING shared TreeType [" << name << "]\n";
        }
        
        return treeTypes[key];
    }
};

// Initialize static member
unordered_map<string, shared_ptr<TreeType>> TreeFactory::treeTypes;


// ==========================================
// 3. Context (Unique Extrinsic State)
// ==========================================
// This object is very lightweight. It only contains coordinates and a pointer to the Flyweight.


class Tree {
private:
    int x;
    int y;
    shared_ptr<TreeType> type; // Pointer to the shared heavy data
public:
    Tree(int x, int y, shared_ptr<TreeType> type) : x(x), y(y), type(type) {}

    void draw() {
        type->draw(x, y); // Delegate drawing to the Flyweight
    }
};


// ==========================================
// 4. Client (The Forest)
// ==========================================
class Forest {
private:
    vector<Tree> trees;
public:
    void plantTree(int x, int y, string name, string color, string texture) {
        // Fetch the shared flyweight type from the factory
        auto type = TreeFactory::getTreeType(name, color, texture);
        
        // Instantiate the lightweight context object
        trees.push_back(Tree(x, y, type));
    }

    void drawForest() {
        for (auto& tree : trees) {
            tree.draw();
        }
    }
};


// ==========================================
// Main Execution
// ==========================================
int main() {
    Forest forest;

    // Planting thousands of trees, but notice the factory output!
    forest.plantTree(10, 20, "Oak", "Green", "oak_texture.png");
    forest.plantTree(15, 30, "Oak", "Green", "oak_texture.png"); // Reuses Oak
    forest.plantTree(50, 60, "Pine", "Dark Green", "pine_texture.png");
    forest.plantTree(12, 85, "Oak", "Green", "oak_texture.png"); // Reuses Oak
    forest.plantTree(55, 70, "Pine", "Dark Green", "pine_texture.png"); // Reuses Pine

    cout << "\n--- Rendering the entire forest ---\n";
    forest.drawForest();

    return 0;
}