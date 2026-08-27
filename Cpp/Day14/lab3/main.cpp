//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <vector>
#include <chrono>

struct ComplexObject {
    long long data[4]; // 32 bytes per object to make copy operations noticeably expensive

    ComplexObject(long long val) {
        data[0] = val;
        data[1] = val + 1;
        data[2] = val + 2;
        data[3] = val + 3;
    }
};

int main() {
    // 20 million elements to clearly show the reallocation overhead on modern CPUs
    constexpr int SIZE = 20'000'000;

    std::cout << "=== std::vector::reserve() Benchmark ===\n";
    std::cout << "Inserting " << SIZE << " objects (" << (SIZE * sizeof(ComplexObject)) / (1024 * 1024) << " MB)...\n\n";

    // 1. Benchmark WITHOUT reserve()
    auto start1 = std::chrono::high_resolution_clock::now();
    std::vector<ComplexObject> vecNoReserve;

    int reallocations = 0;
    size_t last_capacity = vecNoReserve.capacity();

    for (int i = 0; i < SIZE; ++i) {
        vecNoReserve.emplace_back(i);

        if (vecNoReserve.capacity() != last_capacity) {
            reallocations++;
            last_capacity = vecNoReserve.capacity();
        }
    }
    auto end1 = std::chrono::high_resolution_clock::now();


    // 2. Benchmark WITH reserve()
    auto start2 = std::chrono::high_resolution_clock::now();
    std::vector<ComplexObject> vecReserve;

    // Allocate the exact amount of memory needed UPFRONT.
    vecReserve.reserve(SIZE);

    for (int i = 0; i < SIZE; ++i) {
        vecReserve.emplace_back(i);
    }
    auto end2 = std::chrono::high_resolution_clock::now();

    // Prevent compiler from optimizing the vectors away entirely
    std::cout << "Verification -> NoReserve size: " << vecNoReserve.size()
              << ", Reserve size: " << vecReserve.size() << "\n\n";

    std::chrono::duration<double, std::milli> time1 = end1 - start1;
    std::chrono::duration<double, std::milli> time2 = end2 - start2;

    std::cout << "[Without reserve()] Time: " << time1.count() << " ms\n";
    std::cout << "  -> Reallocations triggered: " << reallocations << " times.\n\n";

    std::cout << "[With reserve()]    Time: " << time2.count() << " ms\n";
    std::cout << "  -> Reallocations triggered: 0 times.\n\n";

    if (time2.count() > 0) {
        double ratio = time1.count() / time2.count();
        std::cout << "Conclusion: reserve() is ~" << ratio << "x faster.\n";
    }

    return 0;
}