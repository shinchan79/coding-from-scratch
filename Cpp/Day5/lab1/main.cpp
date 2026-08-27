//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

// 1. C++17 Selection statement with initializer
void testInitStatement() {
    std::cout << "=== 1. C++17 if (init; condition) ===\n";
    std::vector<int> numbers = {10, 20, 30};

    // 'it' is created and scoped strictly within the if-else block
    if (auto it = std::find(numbers.begin(), numbers.end(), 20); it != numbers.end()) {
        std::cout << "Found value: " << *it << '\n';
    } else {
        std::cout << "Value not found\n";
    }
    // 'it' no longer exists here, keeping the namespace clean.
}

// 2. Switch-case (Jump Tables)
void testSwitchCase(int code) {
    std::cout << "\n=== 2. Switch-case ===\n";

    // For dense, contiguous cases, compiler generates a Jump Table (O(1))
    // instead of sequential if-else checks (O(N)).
    switch (code) {
        case 0: std::cout << "Status: OK\n"; break;
        case 1: std::cout << "Status: WARNING\n"; break;
        case 2: std::cout << "Status: ERROR\n"; break;
        default: std::cout << "Status: UNKNOWN\n"; break;
    }
}

// 3. Branch Prediction Benchmark
void benchmarkBranchPrediction() {
    std::cout << "\n=== 3. Branch Prediction Benchmark ===\n";

    constexpr int SIZE = 30'000'000;
    std::vector<int> data(SIZE);

    // Fill with random data (0 to 255)
    std::mt19937 gen(42);
    std::uniform_int_distribution<> dist(0, 256);
    for (int& x : data) x = dist(gen);

    auto measureTime = [&](const std::string& label) {
        long long sum = 0;
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < SIZE; ++i) {
            // Branch Predictor tries to guess the outcome of this condition
            if (data[i] >= 128) {
                sum += data[i];
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << label << " took: " << elapsed.count() << " ms (Sum: " << sum << ")\n";
    };

    // Test 1: Unpredictable branches
    measureTime("Unsorted array");

    std::cout << "Sorting array...\n";
    std::sort(data.begin(), data.end());

    // Test 2: Highly predictable branches
    measureTime("Sorted array  ");
}

int main() {
    testInitStatement();
    testSwitchCase(1);
    benchmarkBranchPrediction();

    return 0;
}