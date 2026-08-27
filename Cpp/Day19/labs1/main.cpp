//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <algorithm>
#include <chrono>
#include <vector>

// Custom vector class implementing Move Semantics (O(1) transfer) alongside Deep Copy
class MoveVector {
private:
    size_t capacity;
    size_t size;
    int* data;

public:
    // Parameterized Constructor
    explicit MoveVector(size_t cap)
        : capacity(cap), size(cap), data(cap > 0 ? new int[cap] : nullptr) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = static_cast<int>(i + 1);
        }
    }

    // Destructor
    ~MoveVector() {
        delete[] data;
    }

    // 1. Copy Constructor (Deep Copy - O(N))
    MoveVector(const MoveVector& other)
        : capacity(other.capacity), size(other.size), data(other.capacity > 0 ? new int[other.capacity] : nullptr) {
        if (data && other.data) {
            std::copy(other.data, other.data + size, data);
        }
    }

    // 2. Move Constructor (Steal Resources - O(1))
    // Takes an rvalue reference (&&) representing a temporary object about to expire.
    MoveVector(MoveVector&& other) noexcept
        : capacity(other.capacity), size(other.size), data(other.data) {
        // Nullify the source object's pointers so its destructor doesn't delete the stolen memory
        other.capacity = 0;
        other.size = 0;
        other.data = nullptr;
        std::cout << "  [m] Move Constructor: Stealing resources in O(1) time.\n";
    }

    // 3. Move Assignment Operator (O(1))
    MoveVector& operator=(MoveVector&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        // Release current resources
        delete[] data;

        // Steal data from 'other'
        capacity = other.capacity;
        size = other.size;
        data = other.data;

        // Leave 'other' in a valid, empty state
        other.capacity = 0;
        other.size = 0;
        other.data = nullptr;

        std::cout << "  [=m] Move Assignment Operator: Stealing resources.\n";
        return *this;
    }

    size_t getSize() const { return size; }
};

int main() {
    constexpr size_t LARGE_SIZE = 25'000'000; // ~100MB of integers
    std::cout << "=== Benchmarking Copy vs Move with ~100MB Vector ===\n\n";

    // Initialize source vector
    MoveVector sourceVec(LARGE_SIZE);

    // 1. Benchmark Copy Construction (O(N) time complexity)
    auto startCopy = std::chrono::high_resolution_clock::now();
    MoveVector copiedVec = sourceVec; // Triggers Copy Constructor (allocates + copies 100MB)
    auto endCopy = std::chrono::high_resolution_clock::now();

    // 2. Benchmark Move Construction (O(1) time complexity)
    auto startMove = std::chrono::high_resolution_clock::now();
    // std::move casts sourceVec to an rvalue reference, forcing the Move Constructor
    MoveVector movedVec = std::move(sourceVec);
    auto endMove = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> copyTime = endCopy - startCopy;
    std::chrono::duration<double, std::milli> moveTime = endMove - startMove;

    std::cout << "Copy Constructor time: " << copyTime.count() << " ms (O(N) allocation & memory copy)\n";
    std::cout << "Move Constructor time: " << moveTime.count() << " ms (O(1) pointer redirection)\n";

    if (moveTime.count() > 0) {
        std::cout << "-> Move is roughly " << static_cast<int>(copyTime.count() / moveTime.count()) << "x faster!\n";
    }

    return 0;
}