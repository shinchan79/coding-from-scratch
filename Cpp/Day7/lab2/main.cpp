//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <chrono>

// 1. Inlining
// 'inline' is merely a request to the compiler to replace the function call
// with the actual code. The compiler ignores it if the function is too large.
inline long long computeMath(long long a, long long b) {
    return (a * b) + (a / (b + 1));
}

// 2. Normal Recursion
// Extremely slow (O(2^n)) and consumes Stack memory for every call.
long long fibRecursive(long long n) {
    if (n <= 1) return n;
    // NOT a tail call: Addition happens AFTER the recursive calls return.
    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

// 3. Iteration
// Fast (O(n)) and safe (O(1) stack space).
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

// 4. Tail Recursion (TCO)
// The recursive call is the ABSOLUTE LAST operation in the function.
// The compiler optimizes this into a normal loop under the hood.
long long fibTailRecursive(long long n, long long a = 0, long long b = 1) {
    if (n == 0) return a;
    if (n == 1) return b;
    return fibTailRecursive(n - 1, b, a + b);
}

// Helper to benchmark functions
void benchmark(const std::string& name, long long (*func)(long long), long long n) {
    auto start = std::chrono::high_resolution_clock::now();
    long long result = func(n);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> time = end - start;
    std::cout << name << "(" << n << ") = " << result
              << " | Time: " << time.count() << " ms\n";
}

int main() {
    std::cout << "=== 1. Inlining ===\n";
    // At -O2, no actual function call happens here in Assembly.
    std::cout << "Inline result: " << computeMath(10, 20) << "\n\n";

    std::cout << "=== 2. Recursion vs Iteration vs TCO ===\n";
    long long n = 42;

    benchmark("Iterative      ", fibIterative, n);

    // Lambda wrapper to match the function signature for benchmarking
    benchmark("Tail Recursive ", [](long long x) { return fibTailRecursive(x); }, n);

    // This will take noticeably longer
    benchmark("Normal Recursion", fibRecursive, n);

    return 0;
}