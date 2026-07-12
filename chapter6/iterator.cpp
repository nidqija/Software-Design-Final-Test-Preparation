#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;



// Iterator Design Pattern
// Intent: Provide a way to access the elements of an aggregate object sequentially without exposing its underlying representation.


// other example use case for iterator design pattern:
// 1. Collection Traversal: In a collection class (like a list, set, or map), the Iterator pattern allows clients to traverse the elements without needing to know the internal structure of the collection.
// 2. Database Result Sets: When retrieving data from a database, an iterator can be used to traverse the rows of a result set without exposing the underlying database implementation.
// 3. File System Navigation: An iterator can be used to traverse files and directories in a file system, allowing clients to access files without needing to know the underlying file system structure.

// Consequences of using the Iterator Design Pattern:
// 1. Simplified Access: The Iterator pattern provides a uniform way to access elements in a collection, making it easier for clients to work with different types of collections.
// 2. Encapsulation: It encapsulates the traversal logic, allowing the collection to change its internal structure without affecting clients.
// 3. Multiple Traversals: Different iterators can be created for the same collection, allowing multiple traversals with different behaviors (e.g., forward, backward, filtered).
// 4. Increased Complexity: Introducing iterators can add complexity to the codebase, especially if multiple iterator types are needed for different traversal strategies.


// COmponents of the Iterator Design Pattern:
// 1. Iterator Interface: Defines the methods for traversing elements (e.g., hasNext(), next()).
// 2. Concrete Iterator: Implements the Iterator interface and maintains the current position in the traversal.
// 3. Collection Interface (Aggregate): Defines a method to create an iterator for the collection.
// 4. Concrete Collection: Implements the collection interface and provides an iterator for its elements.


// internal iterator is an iterator that is implemented within the collection class itself,
// allowing clients to traverse the collection without needing to create a separate iterator object. 
// It typically provides methods for iteration directly on the collection, 
// such as forEach or map, and abstracts away the details of the traversal process.

// external iterator is an iterator that is implemented as a separate object,
// allowing clients to traverse the collection independently of the collection's internal structure.
// It provides methods like hasNext() and next() to control the iteration process,
// giving clients more flexibility in how they traverse the collection.



// Terms in the context of this example:
// 1. Cursor : A cursor is a pointer or reference that keeps track of the current position in a collection during iteration. 
//   It allows the iterator to know which element to return next and helps manage the traversal state.


// Forward declaration
class ChannelIterator;

// ==========================================
// 1. Collection Interface (Aggregate)
// ==========================================
class AbstractCollection {
public:
    virtual unique_ptr<ChannelIterator> createIterator() = 0;
    virtual ~AbstractCollection() = default;
};


// ==========================================
// 2. Iterator Interface
// ==========================================
class ChannelIterator {
public:
    virtual bool hasNext() = 0;
    virtual string next() = 0;
    virtual ~ChannelIterator() = default;
};


// ==========================================
// 3. Concrete Collection
// ==========================================
class RadioStationList : public AbstractCollection {
private:
    vector<string> channels;
public:
    void addChannel(const string& channel) {
        channels.push_back(channel);
    }

    size_t getSize() const {
        return channels.size();
    }

    string getAt(size_t index) const {
        return channels[index];
    }

    // Factory method to generate the corresponding iterator
    unique_ptr<ChannelIterator> createIterator() override;
};


// ==========================================
// 4. Concrete Iterator
// ==========================================
class ConcreteChannelIterator : public ChannelIterator {
private:
    const RadioStationList& collection;
    size_t position = 0; // Tracks current index
public:
    ConcreteChannelIterator(const RadioStationList& coll) : collection(coll) {}

    bool hasNext() override {
        return position < collection.getSize();
    }

    string next() override {
        if (!hasNext()) {
            return "";
        }
        return collection.getAt(position++);
    }
};




// Implementation of the factory method defined inside the collection
unique_ptr<ChannelIterator> RadioStationList::createIterator() {
    return make_unique<ConcreteChannelIterator>(*this);
}


// ==========================================
// Client Code
// ==========================================
int main() {
    RadioStationList myRadio;
    myRadio.addChannel("98.1 FM - Rock Classic");
    myRadio.addChannel("102.5 FM - Jazz Smooth");
    myRadio.addChannel("89.3 FM - Indie Beats");
    myRadio.addChannel("107.9 FM - Top 40 Hits");

    // Get the iterator from the collection
    unique_ptr<ChannelIterator> it = myRadio.createIterator();

    cout << "--- Scanning Radio Channels ---" << endl;
    
    // Traversal loop completely abstracts away the 'vector' storage mechanism
    while (it->hasNext()) {
        cout << "Tuning into: " << it->next() << endl;
    }

    return 0;
}