//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <algorithm>

// A custom dynamic buffer class demonstrating the Rule of Three and Deep Copy
class CustomBuffer {
private:
    size_t capacity;
    int* data;

public:
    // Parameterized Constructor
    explicit CustomBuffer(size_t cap) : capacity(cap), data(cap > 0 ? new int[cap] : nullptr) {
        std::cout << "  [+] Constructor: Allocated " << capacity << " integers on Heap at " << (void*)data << '\n';
        for (size_t i = 0; i < capacity; ++i) {
            data[i] = static_cast<int>((i + 1) * 10);
        }
    }

    // 1. Destructor (Rule of Three - Part 1)
    // Ensures raw heap memory is properly released when the object goes out of scope.
    ~CustomBuffer() {
        std::cout << "  [-] Destructor: Freeing memory at " << (void*)data << '\n';
        delete[] data;
    }

    // 2. Copy Constructor (Rule of Three - Part 2)
    // Performs a Deep Copy to prevent shallow-copy issues (double free / shared raw pointers).
    CustomBuffer(const CustomBuffer& other) : capacity(other.capacity), data(other.capacity > 0 ? new int[other.capacity] : nullptr) {
        std::cout << "  [c] Copy Constructor: Deep copy triggered for capacity " << capacity << '\n';
        if (data && other.data) {
            std::copy(other.data, other.data + capacity, data);
        }
    }

    // 3. Copy Assignment Operator (Rule of Three - Part 3)
    // Manages deep copy assignment safely while protecting against self-assignment.
    CustomBuffer& operator=(const CustomBuffer& other) {
        std::cout << "  [=] Copy Assignment Operator triggered\n";

        // Crucial Self-Assignment Protection
        // Without this, 'buf = buf;' would delete its own data before attempting to copy from it.
        if (this == &other) {
            return *this;
        }

        // Allocate new memory first (Strong Exception Safety approach)
        int* newData = other.capacity > 0 ? new int[other.capacity] : nullptr;
        if (newData && other.data) {
            std::copy(other.data, other.data + other.capacity, newData);
        }

        // Clean up old resources only after successful new allocation
        delete[] data;

        capacity = other.capacity;
        data = newData;

        return *this;
    }

    // Utility function to print buffer contents
    void print() const {
        std::cout << "  Buffer data (capacity: " << capacity << "): ";
        for (size_t i = 0; i < capacity; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << '\n';
    }
};

int main() {
    std::cout << "=== 1. Testing Parameterized Constructor ===\n";
    CustomBuffer buf1(4);
    buf1.print();

    std::cout << "\n=== 2. Testing Copy Constructor (Rule of Three) ===\n";
    {
        // Invokes the custom Copy Constructor (Deep Copy)
        CustomBuffer buf2 = buf1;
        buf2.print();
        std::cout << "Exiting inner scope (buf2 destructor will run)...\n";
    } // buf2 is destroyed here, but buf1's data remains completely intact and safe.

    std::cout << "buf1 is still valid after buf2 is destroyed:\n";
    buf1.print();

    std::cout << "\n=== 3. Testing Copy Assignment Operator ===\n";
    CustomBuffer buf3(2);
    buf3.print();

    // Invokes the custom Copy Assignment Operator
    buf3 = buf1;
    buf3.print();

    std::cout << "\n=== 4. Testing Self-Assignment Protection (if(this == &other)) ===\n";
    // Directly assigning an object to itself
    buf1 = buf1;
    buf1.print();

    std::cout << "\nProgram terminating. buf1 and buf3 will be cleaned up safely.\n";
    return 0;
}