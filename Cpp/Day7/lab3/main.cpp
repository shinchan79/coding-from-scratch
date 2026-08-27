//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <vector>
#include <chrono>
#include <functional>

// --- Helper to measure time ---
template <typename Func>
void measureTime(const std::string& label, Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms = end - start;
    std::cout << label << " took: " << ms.count() << " ms\n";
}

// === 1. Fibonacci 3 Ways ===
long long fibRecursive(long long n) {
    if (n <= 1) return n;
    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

long long fibTailRecursive(long long n, long long a = 0, long long b = 1) {
    if (n == 0) return a;
    if (n == 1) return b;
    return fibTailRecursive(n - 1, b, a + b);
}

long long fibIterative(long long n) {
    if (n <= 1) return n;
    long long a = 0, b = 1, c = 0;
    for (long long i = 2; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

// === 2. Cache Locality (Strategy for next 4 days) ===
void benchmarkCacheLocality() {
    constexpr int N = 10000;
    // 1D vector used to simulate a 2D matrix (N x N) in contiguous memory
    std::vector<int> matrix(N * N, 1);

    // volatile prevents the compiler from optimizing the loops away
    volatile long long sumRow = 0;
    volatile long long sumCol = 0;

    std::cout << "\n=== Cache Locality Benchmark (" << N << "x" << N << ") ===\n";

    // Row-major: Accessing memory sequentially (Cache Hit)
    measureTime("Row-major (Cache friendly)   ", [&]() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                sumRow += matrix[i * N + j];
            }
        }
    });

    // Column-major: Jumping across memory (Cache Miss)
    measureTime("Column-major (Cache unfriendly)", [&]() {
        for (int j = 0; j < N; ++j) {
            for (int i = 0; i < N; ++i) {
                sumCol += matrix[i * N + j];
            }
        }
    });
}

int main() {
    constexpr long long N = 40;

    std::cout << "=== Fibonacci(" << N << ") Benchmark ===\n";
    measureTime("Iterative     ", [N]() { volatile auto res = fibIterative(N); (void)res; });
    measureTime("Tail Recursive", [N]() { volatile auto res = fibTailRecursive(N); (void)res; });
    measureTime("Normal Recurse", [N]() { volatile auto res = fibRecursive(N); (void)res; });

    benchmarkCacheLocality();

    return 0;
}