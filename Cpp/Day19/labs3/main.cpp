//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <vector>
#include <chrono>
#include <utility>

// Function that accepts a vector by copy (Triggers Copy Constructor)
void processByCopy(std::vector<int> vec) {
    // Volatile read to prevent compiler from optimizing away the parameter
    volatile size_t s = vec.size();
    (void)s;
}

// Function that accepts a vector by move (Triggers Move Constructor)
void processByMove(std::vector<int>&& vec) {
    // We can steal or take ownership of the vector locally if needed
    std::vector<int> localVec = std::move(vec);
    volatile size_t s = localVec.size();
    (void)s;
}

int main() {
    // 100MB of integers: 100 * 1024 * 1024 / sizeof(int) ≈ 26,214,400 elements
    constexpr size_t ELEMENT_COUNT = 26'214'400;

    std::cout << "=== Lab: Copy vs Move with 100MB std::vector ===\n";
    std::cout << "Allocating source vector (~100MB)...\n";

    std::vector<int> sourceVector(ELEMENT_COUNT, 42);
    std::cout << "Source vector ready. Capacity: "
              << (sourceVector.capacity() * sizeof(int)) / (1024 * 1024) << " MB\n\n";

    // 1. Benchmark passing by COPY
    auto startCopy = std::chrono::high_resolution_clock::now();

    // Passing 'sourceVector' directly forces a copy.
    // The OS must allocate a brand-new 100MB block and copy all 26M integers.
    processByCopy(sourceVector);

    auto endCopy = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> copyDuration = endCopy - startCopy;

    // Verify sourceVector is still intact after copy
    std::cout << "[Pass by Copy] Time taken : " << copyDuration.count() << " ms\n";
    std::cout << "  -> Source vector size after copy: " << sourceVector.size() << " elements (Intact)\n\n";


    // 2. Benchmark passing by MOVE
    auto startMove = std::chrono::high_resolution_clock::now();

    // std::move casts 'sourceVector' to an rvalue reference (std::vector<int>&&).
    // This forces processByMove to steal the internal pointer in O(1) time.
    processByMove(std::move(sourceVector));

    auto endMove = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> moveDuration = endMove - startMove;

    std::cout << "[Pass by Move] Time taken : " << moveDuration.count() << " ms\n";
    std::cout << "  -> Source vector size after move: " << sourceVector.size() << " elements (Stolen/Empty)\n\n";

    if (moveDuration.count() > 0) {
        double speedup = copyDuration.count() / moveDuration.count();
        std::cout << "Conclusion: Passing by move is roughly " << static_cast<int>(speedup) << "x faster!\n";
    }

    return 0;
}