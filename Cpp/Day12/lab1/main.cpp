//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <chrono>

struct ScopedEntity {
    int id;
    explicit ScopedEntity(int i) : id(i) {
        std::cout << "  [+] Entity " << id << " allocated on Stack.\n";
    }
    ~ScopedEntity() {
        std::cout << "  [-] Entity " << id << " destroyed (Stack Unwinding).\n";
    }
};

// 1. Scope & Stack Unwinding
void demonstrateStackUnwinding() {
    std::cout << "=== 1. Scope & Stack Unwinding ===\n";

    ScopedEntity e1(1);
    {
        ScopedEntity e2(2);
        std::cout << "  -> Exiting inner scope...\n";
    } // e2 is automatically popped off the stack here

    std::cout << "  -> Exiting outer scope...\n";
} // e1 is automatically popped off the stack here

// 2. Performance & Cache Benchmark
void benchmarkStackVsHeap() {
    std::cout << "\n=== 2. Stack vs Heap Benchmark (10M Iterations) ===\n";
    constexpr int ITERATIONS = 10'000'000;

    // Test A: Heap Allocation
    auto startHeap = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERATIONS; ++i) {
        // Asks OS for memory. Involves freelist search and potential cache misses.
        volatile int* ptr = new int(i);
        delete ptr;
    }
    auto endHeap = std::chrono::high_resolution_clock::now();

    // Test B: Stack Allocation
    auto startStack = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERATIONS; ++i) {
        // Only moves the stack pointer by 4 bytes.
        // Reuses the exact same L1 cache line every iteration.
        volatile int val = i;
        (void)val;
    }
    auto endStack = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> timeHeap = endHeap - startHeap;
    std::chrono::duration<double, std::milli> timeStack = endStack - startStack;

    std::cout << "Heap (new/delete) time   : " << timeHeap.count() << " ms\n";
    std::cout << "Stack (pointer move) time: " << timeStack.count() << " ms\n";
}

int main() {
    demonstrateStackUnwinding();
    benchmarkStackVsHeap();
    return 0;
}