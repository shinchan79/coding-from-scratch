//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <vector>
#include <chrono>

// 1. Loop Assembly Differences
void testMachineCodeLoops() {
    volatile int sum = 0;

    // Normal for/while typically generates a check at the top and a jump at the bottom.
    for (int i = 0; i < 5; ++i) {
        sum += i;
    }

    // A do-while generates only one conditional jump at the bottom.
    // Compilers often optimize standard 'for' loops into this pattern automatically.
    int k = 0;
    if (k < 5) {
        do {
            sum += k;
            ++k;
        } while (k < 5);
    }
}

// 2. Range-for under the hood
void testRangeFor() {
    std::cout << "=== Range-for vs Iterators ===\n";
    std::vector<int> nums = {10, 20, 30};

    std::cout << "Range-for: ";
    for (int n : nums) {
        std::cout << n << " ";
    }

    std::cout << "\nIterators (Compiler's perspective): ";
    // This is exactly what the compiler generates for the range-for loop above
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        int n = *it;
        std::cout << n << " ";
    }
    std::cout << "\n\n";
}

// 3. Loop Unrolling Benchmark
void benchmarkLoopUnrolling() {
    std::cout << "=== Loop Unrolling Benchmark ===\n";
    constexpr int SIZE = 100'000'000;
    std::vector<int> data(SIZE, 1);

    // volatile prevents the compiler from optimizing the entire loop away
    volatile long long sum1 = 0;
    volatile long long sum2 = 0;

    // Standard loop
    auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < SIZE; ++i) {
        sum1 += data[i];
    }
    auto end1 = std::chrono::high_resolution_clock::now();

    // Unrolled loop (Factor of 4)
    auto start2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < SIZE; i += 4) {
        sum2 += data[i];
        sum2 += data[i+1];
        sum2 += data[i+2];
        sum2 += data[i+3];
    }
    auto end2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> time1 = end1 - start1;
    std::chrono::duration<double, std::milli> time2 = end2 - start2;

    std::cout << "Standard loop took: " << time1.count() << " ms\n";
    std::cout << "Unrolled loop took: " << time2.count() << " ms\n";
}

int main() {
    testMachineCodeLoops();
    testRangeFor();
    benchmarkLoopUnrolling();
    return 0;
}