#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>



// =========================================================================== //

// PART 3 : DETAILED DESIGN COMPONENT
// in this part , we will discuss the detailed design component of software design phases
// we are providing a detailed design of the system by specifying the data structures , algorithms , and implementation details of each component
// in this use case , we are doing a simple inventory management system for a simple audio player application

// Concrete data structures defined in detailed design
struct Item {
    std::string id;
    std::string name;
    double weightPerItem;
};

// Detailed design design decision: Use an enum class for explicit error handling
enum class InventoryResult {
    Success,
    ItemNotFound,
    OverweightLimit,
    InvalidQuantity
};

class InventorySystem {
private:
    // Detailed Design Decision: 
    // Use an unordered_map (hash table) for O(1) constant-time item lookups.
    // Map key: item_id, Value: pair of <Item data, current quantity>
    std::unordered_map<std::string, std::pair<Item, int>> slots;
    
    double currentWeight = 0.0;
    const double maxWeightCapacity;

public:
    // Constructor enforces invariants (rules that must always be true)
    explicit InventorySystem(double maxWeight) : maxWeightCapacity(maxWeight) {}

    
    // Detailed Design: Concrete algorithmic logic for adding items
    InventoryResult addItem(const Item& item, int quantity) {
        if (quantity <= 0) {
            return InventoryResult::InvalidQuantity;
        }

        // Detailed Design Calculation: Prevent state corruption by checking weight FIRST
        double addedWeight = item.weightPerItem * quantity;


        if (currentWeight + addedWeight > maxWeightCapacity) {
            return InventoryResult::OverweightLimit; // Fail safely
        }

        // If item exists, update quantity; otherwise, insert new map node
        if (slots.find(item.id) != slots.end()) {
            slots[item.id].second += quantity;
        } else {
            slots[item.id] = {item, quantity};
        }

        currentWeight += addedWeight;
        return InventoryResult::Success;

    }

    // Concrete retrieval logic
    int getItemQuantity(const std::string& itemId) const {

        auto it = slots.find(itemId);
        if (it != slots.end()) {
            return it->second.second; // Return the quantity
        }

        return 0;
    }

    double getCurrentWeight() const { return currentWeight; }
};

// =========================================================================== //
// SIMULATION
// =========================================================================== //

int main() {
    // Instantiate our detailed design implementation with a 50.0 kg limit
    InventorySystem playerInventory(50.0);

    Item ironOre{"item_iron_01", "Iron Ore", 5.0};      // 5kg each
    Item healingPotion{"item_pot_01", "Health Potion", 0.5}; // 0.5kg each

    std::cout << "--- Detailed Design Execution ---\n";

    // 1. Try a normal insertion
    if (playerInventory.addItem(ironOre, 4) == InventoryResult::Success) {
        std::cout << "Successfully added 4 Iron Ores.\n";
    }

    // 2. Try an invalid operation
    if (playerInventory.addItem(healingPotion, -5) == InventoryResult::InvalidQuantity) {
        std::cout << "Error Caught: Cannot add negative items.\n";
    }

    // 3. Test data boundaries (Triggering the max weight protection)
    std::cout << "Attempting to add 10 more Iron Ores (50kg total)... \n";
    InventoryResult result = playerInventory.addItem(ironOre, 10);
    
    if (result == InventoryResult::OverweightLimit) {
        std::cout << "Action Denied: Inventory would exceed maximum weight capacity!\n";
    }

    std::cout << "\nFinal Inventory Weight: " << playerInventory.getCurrentWeight() << " kg\n";
    std::cout << "Total Iron Ore count: " << playerInventory.getItemQuantity("item_iron_01") << "\n";

    return 0;
}