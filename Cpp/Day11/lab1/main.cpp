//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>

struct Block {
    int data[256]; // 1KB payload
};

struct LargerBlock {
    int data[300]; // 1.2KB payload
};

// 1. Simulate Memory Fragmentation
void demonstrateFragmentation() {
    std::cout << "=== 1. Memory Fragmentation Simulation ===\n";
    constexpr int SIZE = 10000;
    std::vector<Block*> heapBlocks(SIZE);

    // Allocate 10,000 continuous 1KB blocks
    for (int i = 0; i < SIZE; ++i) {
        heapBlocks[i] = new Block();
    }

    std::cout << "Address of Block 0: " << heapBlocks[0] << '\n';
    std::cout << "Address of Block 1: " << heapBlocks[1] << '\n';

    // Create external fragmentation (Swiss cheese) by freeing alternating blocks
    for (int i = 0; i < SIZE; i += 2) {
        delete heapBlocks[i];
        heapBlocks[i] = nullptr;
    }

    // Request a 1.2KB block.
    // The OS cannot use the 1KB holes, so it must search elsewhere or request more RAM.
    LargerBlock* awkwardBlock = new LargerBlock();
    std::cout << "Allocated 1.2KB block at: " << awkwardBlock << " (Scattered due to fragmentation)\n\n";

    // Cleanup remaining memory
    delete awkwardBlock;
    for (int i = 1; i < SIZE; i += 2) {
        delete heapBlocks[i];
    }
}

// 2. OS Memory Manager Overhead Benchmark
void benchmarkHeapOverhead() {
    std::cout << "=== 2. OS Memory Manager Overhead ===\n";
    constexpr int ITERATIONS = 1'000'000;

    // Test A: Calling OS allocator 1,000,000 times
    auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERATIONS; ++i) {
        volatile int* ptr = new int(i);
        delete ptr;
    }
    auto end1 = std::chrono::high_resolution_clock::now();

    // Test B: Calling OS allocator exactly ONCE (Pre-allocation / Pool)
    auto start2 = std::chrono::high_resolution_clock::now();
    int* memoryPool = new int[ITERATIONS];
    for (int i = 0; i < ITERATIONS; ++i) {
        memoryPool[i] = i;
    }
    delete[] memoryPool;
    auto end2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> time1 = end1 - start1;
    std::chrono::duration<double, std::milli> time2 = end2 - start2;

    std::cout << "Individual new/delete time: " << time1.count() << " ms\n";
    std::cout << "Pre-allocated pool time   : " << time2.count() << " ms\n";
}

int main() {
    demonstrateFragmentation();
    benchmarkHeapOverhead();
    return 0;
}