//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <algorithm>
#include <cstring>

// Custom vector class managing raw heap memory to demonstrate Copy Semantics
class MyVector {
private:
    size_t size;
    int* data;

public:
    // Parameterized Constructor
    explicit MyVector(size_t s) : size(s), data(s > 0 ? new int[s] : nullptr) {
        std::cout << "  [+] Parameterized Constructor: Allocated " << size << " ints at " << (void*)data << '\n';
        for (size_t i = 0; i < size; ++i) {
            data[i] = static_cast<int>(i + 1);
        }
    }

    // Destructor (Rule of Three part 1)
    ~MyVector() {
        std::cout << "  [-] Destructor: Freeing memory at " << (void*)data << '\n';
        delete[] data;
    }

    // 1. Copy Constructor (Rule of Three part 2) - Implements Deep Copy
    MyVector(const MyVector& other) : size(other.size), data(other.size > 0 ? new int[other.size] : nullptr) {
        std::cout << "  [c] Copy Constructor: Deep copy triggered for size " << size << '\n';
        if (data && other.data) {
            std::copy(other.data, other.data + size, data);
        }
    }

    // 2. Copy Assignment Operator (Rule of Three part 3) - Deep Copy + Self-Assignment Protection
    MyVector& operator=(const MyVector& other) {
        std::cout << "  [=] Copy Assignment Operator triggered\n";

        // Protection against self-assignment (e.g., v = v;)
        if (this == &other) {
            return *this;
        }

        // Allocate new memory first (Exception Safety / Strong Guarantee approach)
        int* newData = other.size > 0 ? new int[other.size] : nullptr;
        if (newData && other.data) {
            std::copy(other.data, other.data + other.size, newData);
        }

        // Clean up old memory only after successful allocation
        delete[] data;

        size = other.size;
        data = newData;

        return *this;
    }

    // Utility to print content
    void print() const {
        std::cout << "  Vector data (size: " << size << "): ";
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << '\n';
    }
};

int main() {
    std::cout << "=== 1. Testing Parameterized Constructor ===\n";
    MyVector v1(3);
    v1.print();

    std::cout << "\n=== 2. Testing Copy Constructor (Deep Copy) ===\n";
    {
        // Invokes Copy Constructor
        MyVector v2 = v1;
        v2.print();
        std::cout << "Exiting inner scope (v2 will be destroyed)...\n";
    } // v2 is destroyed here, but v1's data remains intact (no double free!)

    std::cout << "v1 is still completely safe:\n";
    v1.print();

    std::cout << "\n=== 3. Testing Copy Assignment Operator ===\n";
    MyVector v3(2);
    v3.print();

    // Invokes Copy Assignment Operator
    v3 = v1;
    v3.print();

    std::cout << "\n=== 4. Testing Self-Assignment Protection ===\n";
    // Self-assignment should safely do nothing
    v1 = v1;
    v1.print();

    std::cout << "\nProgram ending. v1 and v3 will now be destroyed safely.\n";
    return 0;
}