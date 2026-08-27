//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <chrono>

// 1. C-Array Cache Locality & Row-major vs Column-major
void benchmarkCacheLocality() {
    std::cout << "=== 1. CPU Cache Line Benchmark ===\n";
    constexpr int N = 10000;

    // Allocated on Heap. A 10000x10000 int array takes ~400MB.
    // Putting this on the Stack would cause a Stack Overflow on macOS (8MB limit).
    int* matrix = new int[N * N];

    volatile long long sumRow = 0;
    auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            // Cache HIT: CPU pulls 64 bytes (16 ints) at a time.
            // Accessing contiguous memory utilizes the entire L1 cache line.
            sumRow += matrix[i * N + j];
        }
    }
    auto end1 = std::chrono::high_resolution_clock::now();

    volatile long long sumCol = 0;
    auto start2 = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < N; ++j) {
        for (int i = 0; i < N; ++i) {
            // Cache MISS: Jumping across memory addresses forces the CPU
            // to fetch a new L1 cache line for almost every single operation.
            sumCol += matrix[i * N + j];
        }
    }
    auto end2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> t1 = end1 - start1;
    std::chrono::duration<double, std::milli> t2 = end2 - start2;

    std::cout << "Row-major (Cache friendly)   : " << t1.count() << " ms\n";
    std::cout << "Column-major (Cache unfriendly): " << t2.count() << " ms\n\n";

    delete[] matrix;
}

// 2. Buffer Overflow Risk with C-Arrays
void triggerBufferOverflow() {
    std::cout << "=== 2. Buffer Overflow Risk ===\n";

    // C-arrays do not track their own size and perform zero bounds checking.
    int buffer[3] = {10, 20, 30};

    std::cout << "Valid access: buffer[2] = " << buffer[2] << '\n';
    std::cout << "Executing out-of-bounds write...\n";

    // WARNING: Intentional out-of-bounds access.
    // AddressSanitizer (ASan) will intercept this, print a red error trace,
    // and terminate the program immediately to prevent silent memory corruption.
    buffer[3] = 99;

    // This line will never be reached if ASan is active.
    std::cout << "If you see this, ASan failed: " << buffer[3] << '\n';
}

int main() {
    benchmarkCacheLocality();
    triggerBufferOverflow();
    return 0;
}