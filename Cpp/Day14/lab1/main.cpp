//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <vector>
#include <list>
#include <chrono>

// 1. Size vs Capacity & Reallocation (Amortized O(1))
void demonstrateReallocation() {
    std::cout << "=== 1. Reallocation: Size vs Capacity ===\n";
    std::vector<int> vec;

    std::cout << "Initial -> Size: " << vec.size() << ", Capacity: " << vec.capacity() << '\n';

    size_t last_capacity = vec.capacity();
    int reallocation_count = 0;

    for (int i = 1; i <= 33; ++i) {
        vec.push_back(i);

        // Check if the capacity changed (meaning a reallocation occurred)
        if (vec.capacity() != last_capacity) {
            std::cout << "  [!] Reallocation #" << ++reallocation_count
                      << " triggered at element " << i
                      << " | New Capacity: " << vec.capacity() << '\n';
            last_capacity = vec.capacity();
        }
    }

    std::cout << "Final   -> Size: " << vec.size() << ", Capacity: " << vec.capacity() << "\n\n";
}

// 2. Data Locality: Vector vs List
void benchmarkDataLocality() {
    std::cout << "=== 2. Data Locality: Vector vs List (10M elements) ===\n";
    constexpr int SIZE = 10'000'000;

    // Both containers hold the exact same amount of data
    std::vector<int> vec(SIZE, 1);
    std::list<int> lst(SIZE, 1);

    // Test A: std::vector (Contiguous Memory -> Cache Hit)
    auto start_vec = std::chrono::high_resolution_clock::now();
    volatile long long sum_vec = 0;
    for (int v : vec) {
        sum_vec += v;
    }
    auto end_vec = std::chrono::high_resolution_clock::now();

    // Test B: std::list (Scattered Memory -> Cache Miss)
    auto start_lst = std::chrono::high_resolution_clock::now();
    volatile long long sum_lst = 0;
    for (int l : lst) {
        sum_lst += l;
    }
    auto end_lst = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> time_vec = end_vec - start_vec;
    std::chrono::duration<double, std::milli> time_lst = end_lst - start_lst;

    std::cout << "std::vector time: " << time_vec.count() << " ms\n";
    std::cout << "std::list time  : " << time_lst.count() << " ms\n";

    if (time_vec.count() > 0) {
        std::cout << "-> Vector is ~" << (time_lst.count() / time_vec.count())
                  << "x faster purely due to memory layout!\n";
    }
}

int main() {
    demonstrateReallocation();
    benchmarkDataLocality();
    return 0;
}