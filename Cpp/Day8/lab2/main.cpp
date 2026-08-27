//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <chrono>
#include <iomanip>

// 1. Pointer Chasing (Indirection Overhead)
void benchmarkIndirection() {
    std::cout << "=== 1. Pointer Chasing (Triple Indirection) ===\n";
    constexpr int ITERATIONS = 100'000'000;

    // 'volatile' forces the CPU to actually fetch from RAM,
    // preventing the -O2 compiler from caching the value in a register.
    volatile int data = 42;
    volatile int* p1 = &data;
    volatile int** p2 = &p1;
    volatile int*** p3 = &p2;

    volatile long long sumDirect = 0;
    volatile long long sumPointer = 0;

    // Test A: Direct memory access
    auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERATIONS; ++i) {
        sumDirect += data;
    }
    auto end1 = std::chrono::high_resolution_clock::now();

    // Test B: Triple pointer indirection (Pointer Chasing)
    auto start2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERATIONS; ++i) {
        // CPU has to jump 3 times across memory addresses to find the actual value
        sumPointer += ***p3;
    }
    auto end2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> time1 = end1 - start1;
    std::chrono::duration<double, std::milli> time2 = end2 - start2;

    std::cout << "Direct access time   : " << time1.count() << " ms\n";
    std::cout << "Triple pointer time  : " << time2.count() << " ms\n";
    std::cout << "(Difference represents the CPU overhead of fetching addresses)\n\n";
}

// 2. void* and reinterpret_cast
void testVoidPointer() {
    std::cout << "=== 2. void* & reinterpret_cast ===\n";

    // A 64-bit integer
    long long secretData = 0x1122334455667788;

    // void* completely erases the type information.
    // It only knows WHERE the data is, not WHAT it is.
    void* rawMemory = &secretData;

    // ERROR: You cannot dereference a void* directly.
    // std::cout << *rawMemory;

    // We use reinterpret_cast to brutally force the compiler to read
    // the raw memory bits as whatever type we want.
    int* readAsInt = reinterpret_cast<int*>(rawMemory);
    char* readAsChar = reinterpret_cast<char*>(rawMemory);

    std::cout << std::hex << std::uppercase;
    std::cout << "Original 64-bit data : 0x" << secretData << '\n';

    // Reads only the first 4 bytes (due to little-endian architecture, it reads 55667788)
    std::cout << "Read as 32-bit int   : 0x" << *readAsInt << '\n';

    // Reads only the very first byte
    std::cout << "Read as 8-bit char   : 0x" << (int)(*readAsChar) << '\n';
}

int main() {
    benchmarkIndirection();
    testVoidPointer();
    return 0;
}