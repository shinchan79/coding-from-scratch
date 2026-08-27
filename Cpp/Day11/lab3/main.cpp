//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <cstring>
#include <cstdint>

// 1. Vector vs List: The Cache Line Effect
void benchmarkVectorVsList() {
    std::cout << "=== 1. Vector vs List (Cache Locality) ===\n";
    constexpr int SIZE = 10'000'000;

    std::vector<int> vec(SIZE, 1);
    std::list<int> lst(SIZE, 1);

    // Vector iteration (Contiguous memory)
    auto start1 = std::chrono::high_resolution_clock::now();
    volatile long long sumVec = 0;
    for (int v : vec) {
        sumVec += v;
    }
    auto end1 = std::chrono::high_resolution_clock::now();

    // List iteration (Scattered memory)
    auto start2 = std::chrono::high_resolution_clock::now();
    volatile long long sumLst = 0;
    for (int l : lst) {
        sumLst += l;
    }
    auto end2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> t1 = end1 - start1;
    std::chrono::duration<double, std::milli> t2 = end2 - start2;

    std::cout << "std::vector time: " << t1.count() << " ms (Cache HIT)\n";
    std::cout << "std::list time  : " << t2.count() << " ms (Cache MISS)\n";
    std::cout << "-> Vector is ~" << (t2.count() / t1.count()) << "x faster purely due to memory layout.\n\n";
}

// 2. SlowCopy vs FastCopy (Pointer Arithmetic & Block Size)
void benchmarkCopyMechanisms() {
    std::cout << "=== 2. SlowCopy vs FastCopy ===\n";
    constexpr int SIZE = 10'000'000;
    std::vector<int> src(SIZE, 42);
    std::vector<int> dst(SIZE, 0);

    size_t byteSize = SIZE * sizeof(int);

    // Test A: SlowCopy (Byte-by-byte using 1-byte pointers)
    // 'volatile' prevents the compiler from automatically upgrading this to memcpy
    auto start1 = std::chrono::high_resolution_clock::now();
    volatile char* cSrc = reinterpret_cast<volatile char*>(src.data());
    volatile char* cDst = reinterpret_cast<volatile char*>(dst.data());
    for (size_t i = 0; i < byteSize; ++i) {
        *cDst++ = *cSrc++;
    }
    auto end1 = std::chrono::high_resolution_clock::now();

    // Test B: FastCopy (Pointer arithmetic using 8-byte/64-bit chunks)
    auto start2 = std::chrono::high_resolution_clock::now();
    volatile uint64_t* pSrc = reinterpret_cast<volatile uint64_t*>(src.data());
    volatile uint64_t* pDst = reinterpret_cast<volatile uint64_t*>(dst.data());
    size_t chunkCount = byteSize / sizeof(uint64_t);
    for (size_t i = 0; i < chunkCount; ++i) {
        *pDst++ = *pSrc++;
    }
    auto end2 = std::chrono::high_resolution_clock::now();

    // Test C: Built-in std::memcpy (Hardware SIMD optimized)
    auto start3 = std::chrono::high_resolution_clock::now();
    std::memcpy(dst.data(), src.data(), byteSize);
    auto end3 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> t1 = end1 - start1;
    std::chrono::duration<double, std::milli> t2 = end2 - start2;
    std::chrono::duration<double, std::milli> t3 = end3 - start3;

    std::cout << "1-Byte Pointer copy (*char)   : " << t1.count() << " ms\n";
    std::cout << "8-Byte Pointer copy (*uint64) : " << t2.count() << " ms\n";
    std::cout << "std::memcpy (SIMD intrinsic)  : " << t3.count() << " ms\n";
}

int main() {
    benchmarkVectorVsList();
    benchmarkCopyMechanisms();
    return 0;
}