//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <algorithm>
#include <cstddef>

// Upgraded custom vector class implementing complete Deep Copy (Rule of Three)
class MyVector {
private:
    size_t capacity;
    size_t size;
    int* data;

public:
    // Parameterized Constructor
    explicit MyVector(size_t cap)
        : capacity(cap), size(cap), data(cap > 0 ? new int[cap] : nullptr) {
        std::cout << "  [+] Parameterized Constructor: Allocated " << capacity << " elements at " << (void*)data << '\n';
        for (size_t i = 0; i < size; ++i) {
            data[i] = static_cast<int>((i + 1) * 5);
        }
    }

    // 1. Destructor (Rule of Three - Part 1)
    ~MyVector() {
        std::cout << "  [-] Destructor: Releasing heap memory at " << (void*)data << '\n';
        delete[] data;
    }

    // 2. Copy Constructor (Rule of Three - Part 2) - Implements Deep Copy
    MyVector(const MyVector& other)
        : capacity(other.capacity), size(other.size), data(other.capacity > 0 ? new int[other.capacity] : nullptr) {
        std::cout << "  [c] Copy Constructor: Triggered deep copy for capacity " << capacity << '\n';
        if (data && other.data) {
            std::copy(other.data, other.data + size, data);
        }
    }

    // 3. Copy Assignment Operator (Rule of Three - Part 3) - Deep Copy + Self-Assignment Protection
    MyVector& operator=(const MyVector& other) {
        std::cout << "  [=] Copy Assignment Operator: Triggered assignment\n";

        // Step A: Guard against self-assignment (e.g., vec = vec;)
        if (this == &other) {
            return *this;
        }

        // Step B: Allocate new memory first (Strong Exception Safety)
        int* newData = other.capacity > 0 ? new int[other.capacity] : nullptr;
        if (newData && other.data) {
            std::copy(other.data, other.data + other.size, newData);
        }

        // Step C: Delete old resources only after successful allocation
        delete[] data;

        // Step D: Update member states
        capacity = other.capacity;
        size = other.size;
        data = newData;

        return *this;
    }

    // Utility display method
    void print() const {
        std::cout << "  Vector contents (size: " << size << ", capacity: " << capacity << "): ";
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << '\n';
    }
};

int main() {
    std::cout << "=== 1. Initializing Source Vector ===\n";
    MyVector v1(3);
    v1.print();

    std::cout << "\n=== 2. Testing Deep Copy Constructor ===\n";
    {
        // Triggers the custom Copy Constructor
        MyVector v2 = v1;
        v2.print();
        std::cout << "Exiting inner scope (v2 destructor will execute now)...\n";
    } // v2 goes out of scope and is destroyed here, but v1 remains fully intact (no double free!)

    std::cout << "Verifying v1 remains completely safe:\n";
    v1.print();

    std::cout << "\n=== 3. Testing Deep Copy Assignment Operator ===\n";
    MyVector v3(1);
    v3.print();

    // Triggers the custom Copy Assignment Operator
    v3 = v1;
    v3.print();

    std::cout << "\n=== 4. Testing Self-Assignment Protection ===\n";
    // Directly assigning an instance to itself
    v1 = v1;
    v1.print();

    std::cout << "\nProgram execution completed. Cleaning up remaining instances.\n";
    return 0;
}