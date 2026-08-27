//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

std::vector<int> generateData(int size) {
    std::vector<int> data(size);
    std::mt19937 gen(42);
    std::uniform_int_distribution<> dist(0, 255);
    for (int& x : data) x = dist(gen);
    return data;
}

void benchmarkSearch(const std::vector<int>& data, const std::string& label) {
    long long sum = 0;
    auto start = std::chrono::high_resolution_clock::now();

    for (int val : data) {
        // CPU Branch Predictor tries to guess this condition
        if (val >= 128) {
            sum += val;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << label << " took: " << elapsed.count() << " ms (Sum: " << sum << ")\n";
}

void benchmarkAttributes(const std::vector<int>& data) {
    std::cout << "\n=== 2. C++20 [[likely]] / [[unlikely]] ===\n";
    int rareValue = 255;
    int rareCount = 0;

    auto start = std::chrono::high_resolution_clock::now();

    for (int val : data) {
        // We hint the compiler that finding '255' is extremely rare (1/256 chance)
        if (val == rareValue) [[unlikely]] {
            rareCount++;
        } else [[likely]] {
            // dummy variable to prevent the compiler from optimizing the loop away
            volatile int dummy = val;
            (void)dummy;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Attribute search took: " << elapsed.count() << " ms (Found: " << rareCount << ")\n";
}

int main() {
    constexpr int SIZE = 50'000'000;
    std::cout << "Generating " << SIZE << " random numbers...\n\n";
    std::vector<int> data = generateData(SIZE);

    std::cout << "=== 1. Branch Prediction (Unsorted vs Sorted) ===\n";
    benchmarkSearch(data, "Unsorted array filter");

    std::cout << "Sorting array...\n";
    std::sort(data.begin(), data.end());

    benchmarkSearch(data, "Sorted array filter  ");

    benchmarkAttributes(data);

    return 0;
}