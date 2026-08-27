//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <string>
#include <vector>
#include <memory>

// ==========================================
// 1. RULE OF FIVE IMPLEMENTATION
// ==========================================
class ManagedResource {
private:
    size_t size;
    int* data;

public:
    // 1. Parameterized Constructor
    explicit ManagedResource(size_t s)
        : size(s), data(s > 0 ? new int[s] : nullptr) {
        std::cout << "  [+] Constructor: Allocated " << size << " elements at " << (void*)data << '\n';
        for (size_t i = 0; i < size; ++i) {
            data[i] = static_cast<int>(i + 10);
        }
    }

    // 2. Destructor (Rule of 5 - #1)
    ~ManagedResource() {
        std::cout << "  [-] Destructor: Releasing memory at " << (void*)data << '\n';
        delete[] data;
    }

    // 3. Copy Constructor (Rule of 5 - #2) - Deep Copy
    ManagedResource(const ManagedResource& other)
        : size(other.size), data(other.size > 0 ? new int[other.size] : nullptr) {
        std::cout << "  [c] Copy Constructor: Deep copy triggered.\n";
        if (data && other.data) {
            std::copy(other.data, other.data + size, data);
        }
    }

    // 4. Copy Assignment Operator (Rule of 5 - #3) - Deep Copy + Self-Assignment Protection
    ManagedResource& operator=(const ManagedResource& other) {
        std::cout << "  [=] Copy Assignment Operator triggered.\n";
        if (this == &other) {
            return *this;
        }

        int* newData = other.size > 0 ? new int[other.size] : nullptr;
        if (newData && other.data) {
            std::copy(other.data, other.data + other.size, newData);
        }

        delete[] data;
        size = other.size;
        data = newData;

        return *this;
    }

    // 5. Move Constructor (Rule of 5 - #4) - O(1) Resource Stealing
    ManagedResource(ManagedResource&& other) noexcept
        : size(other.size), data(other.data) {
        other.size = 0;
        other.data = nullptr;
        std::cout << "  [m] Move Constructor: Stolen resources successfully.\n";
    }

    // 6. Move Assignment Operator (Rule of 5 - #5) - O(1) Resource Stealing
    ManagedResource& operator=(ManagedResource&& other) noexcept {
        std::cout << "  [=m] Move Assignment Operator triggered.\n";
        if (this == &other) {
            return *this;
        }

        delete[] data;

        size = other.size;
        data = other.data;

        other.size = 0;
        other.data = nullptr;

        return *this;
    }

    void print() const {
        std::cout << "  Resource size: " << size << ", Data address: " << (void*)data << '\n';
    }
};


// ==========================================
// 2. RULE OF ZERO IMPLEMENTATION
// ==========================================
// By using modern C++ abstractions (std::vector, std::unique_ptr, std::string),
// this class manages its own resources automatically.
// We write 0 custom constructors for resource management, 0 destructors, and 0 copy/move operators!
class ModernPlayer {
private:
    std::string name;                          // Handled automatically by std::string
    int level;                                 // Primitive type
    std::unique_ptr<ManagedResource> resource; // Handled automatically by smart pointers
    std::vector<int> inventory;                // Handled automatically by STL containers

public:
    // Only a standard parameterized constructor is needed to initialize values.
    ModernPlayer(std::string playerName, int lvl, size_t resSize)
        : name(std::move(playerName)),
          level(lvl),
          resource(std::make_unique<ManagedResource>(resSize)),
          inventory({100, 200, 300}) {
        std::cout << "  [ModernPlayer] Created player: " << name << '\n';
    }

    // Destructor? Not needed!
    // Copy Constructor? Automatically generated and works out of the box!
    // Move Constructor? Automatically generated and optimized!

    void printInfo() const {
        std::cout << "  Player: " << name << " (Level " << level << ")\n";
    }
};

int main() {
    std::cout << "=== 1. Testing Rule of Five ===\n";
    {
        ManagedResource res1(5);

        // Testing Move Constructor
        ManagedResource res2 = std::move(res1);
        res2.print();
    } // Both instances clean up properly without double-free errors

    std::cout << "\n=== 2. Testing Rule of Zero ===\n";
    {
        ModernPlayer player1("HeroAlpha", 99, 3);
        player1.printInfo();

        std::cout << "  -> Copying player1 to player2...\n";
        ModernPlayer player2 = player1; // Compiler automatically synthesizes a safe deep copy!
        player2.printInfo();
    } // Exiting scope: all components (string, unique_ptr, vector) clean up cleanly with zero memory leaks

    std::cout << "\nProgram terminated successfully.\n";
    return 0;
}