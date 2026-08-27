//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <vector>
#include <chrono>

struct SmallBlock { char data[64]; };
struct LargeBlock { char data[128]; };

// 1. Benchmark allocation on a fresh, clean heap
void benchmarkCleanHeap() {
    constexpr int ALLOC_COUNT = 100'000;
    std::vector<LargeBlock*> cleanBlocks(ALLOC_COUNT);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ALLOC_COUNT; ++i) {
        cleanBlocks[i] = new LargeBlock();
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Clean Heap Allocation Time     : " << elapsed.count() << " ms\n";

    // Cleanup
    for (auto ptr : cleanBlocks) delete ptr;
}

// 2. Benchmark allocation on a severely fragmented heap
void benchmarkFragmentedHeap() {
    constexpr int FRAGMENT_COUNT = 2'000'000;
    std::vector<SmallBlock*> fragments(FRAGMENT_COUNT);

    // Step A: Fill the heap with millions of small blocks
    for (int i = 0; i < FRAGMENT_COUNT; ++i) {
        fragments[i] = new SmallBlock();
    }

    // Step B: Shred the heap (Create "Swiss cheese" holes)
    // We free every alternate block. The OS now has a massive free-list
    // filled with tiny 64-byte holes scattered across the RAM.
    for (int i = 0; i < FRAGMENT_COUNT; i += 2) {
        delete fragments[i];
        fragments[i] = nullptr;
    }

    constexpr int ALLOC_COUNT = 100'000;
    std::vector<LargeBlock*> testBlocks(ALLOC_COUNT);

    // Step C: Try allocating larger blocks on the ruined heap
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ALLOC_COUNT; ++i) {
        // The OS memory manager attempts to find a 128-byte slot.
        // It scans the free-list, encounters millions of 64-byte holes,
        // rejects them all, and wastes massive CPU cycles before finally
        // allocating new pages.
        testBlocks[i] = new LargeBlock();
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Fragmented Heap Allocation Time: " << elapsed.count() << " ms\n";

    // Cleanup
    for (auto ptr : testBlocks) delete ptr;
    for (int i = 1; i < FRAGMENT_COUNT; i += 2) delete fragments[i];
}

int main() {
    std::cout << "=== Memory Fragmentation Benchmark ===\n";

    benchmarkCleanHeap();

    std::cout << "\nFragmenting heap (allocating & shredding 2 million blocks)...\n";
    benchmarkFragmentedHeap();

    return 0;
}