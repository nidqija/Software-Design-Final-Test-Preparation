#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

// Base class establishing the "contract" for all birds
class Bird {
public:
    virtual void fly() {
        std::cout << "This bird is flying high!" << std::endl;
    }
    virtual ~Bird() {}
};

// A Sparrow is a bird and it can fly perfectly
class Sparrow : public Bird {
    // Uses the default fly() behavior
};

// A Penguin is a bird, but it cannot fly
class Penguin : public Bird {
public:
    
    
};


// A client function that processes a group of birds
void makeBirdsFly(const std::vector<Bird*>& birds) {
    for (Bird* bird : birds) {
        bird->fly(); // This will crash when it hits a Penguin
    }
}


int main(){
    std::vector<Bird*> birds;
    birds.push_back(new Sparrow());
    birds.push_back(new Penguin()); // This will cause an issue

    try {
        makeBirdsFly(birds);
    } catch (const std::logic_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}