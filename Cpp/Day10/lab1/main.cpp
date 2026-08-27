//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>

struct BigStruct {
    double a, b, c, d; // 4 * 8 = 32 bytes
};

// 1. Pointer Arithmetic
void demonstratePointerArithmetic() {
    std::cout << "=== 1. Pointer Arithmetic (ptr + 1) ===\n";

    char c = 'A';
    int i = 42;
    double d = 3.14;
    BigStruct bs;

    char* pc = &c;
    int* pi = &i;
    double* pd = &d;
    BigStruct* pbs = &bs;

    // reinterpret_cast to uintptr_t allows us to safely subtract raw memory addresses
    std::cout << "char*   jump: " << (reinterpret_cast<uintptr_t>(pc + 1) - reinterpret_cast<uintptr_t>(pc)) << " bytes\n";
    std::cout << "int*    jump: " << (reinterpret_cast<uintptr_t>(pi + 1) - reinterpret_cast<uintptr_t>(pi)) << " bytes\n";
    std::cout << "double* jump: " << (reinterpret_cast<uintptr_t>(pd + 1) - reinterpret_cast<uintptr_t>(pd)) << " bytes\n";
    std::cout << "struct* jump: " << (reinterpret_cast<uintptr_t>(pbs + 1) - reinterpret_cast<uintptr_t>(pbs)) << " bytes\n\n";
}

// 2. Iteration: Index vs Pointer
volatile long long sumIndex = 0;
void iterateByIndex(const std::vector<int>& data) {
    for (size_t i = 0; i < data.size(); ++i) {
        sumIndex += data[i]; // Access via index
    }
}

volatile long long sumPointer = 0;
void iterateByPointer(const std::vector<int>& data) {
    const int* ptr = data.data();
    const int* end = ptr + data.size();

    while (ptr != end) {
        sumPointer += *ptr;  // Access via pointer
        ++ptr;               // Move to next element
    }
}

void benchmarkIteration() {
    std::cout << "=== 2. Array[i] vs Pointer Iteration Benchmark ===\n";
    constexpr int SIZE = 100'000'000;
    std::vector<int> data(SIZE, 1);

    auto start1 = std::chrono::high_resolution_clock::now();
    iterateByIndex(data);
    auto end1 = std::chrono::high_resolution_clock::now();

    auto start2 = std::chrono::high_resolution_clock::now();
    iterateByPointer(data);
    auto end2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> time1 = end1 - start1;
    std::chrono::duration<double, std::milli> time2 = end2 - start2;

    std::cout << "Index [i] time   : " << time1.count() << " ms\n";
    std::cout << "Pointer (*ptr) time: " << time2.count() << " ms\n";
}

int main() {
    demonstratePointerArithmetic();
    benchmarkIteration();
    return 0;
}