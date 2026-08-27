//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <chrono>

void benchmarkTriplePointer() {
  // 500 million iterations to make the time difference visible on modern CPUs (like Apple M4)
  constexpr int ITERATIONS = 500'000'000;

  // 'volatile' is strictly required here.
  // It prevents the -O2 compiler from caching the values in CPU registers
  // or optimizing the loop away entirely. It forces a real RAM/Cache fetch every time.
  volatile int data = 42;
  volatile int* p1 = &data;
  volatile int** p2 = &p1;
  volatile int*** p3 = &p2;

  volatile long long sumDirect = 0;
  volatile long long sumPointer = 0;

  std::cout << "=== Pointer Chasing Benchmark (" << ITERATIONS << " loops) ===\n";

  // 1. Direct Variable Access
  auto start1 = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < ITERATIONS; ++i) {
    sumDirect += data;
  }
  auto end1 = std::chrono::high_resolution_clock::now();

  // 2. Triple Pointer Indirection Access
  auto start2 = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < ITERATIONS; ++i) {
    // CPU must resolve p3 -> p2 -> p1 -> data sequentially
    sumPointer += ***p3;
  }
  auto end2 = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double, std::milli> time1 = end1 - start1;
  std::chrono::duration<double, std::milli> time2 = end2 - start2;

  std::cout << "Direct access time  : " << time1.count() << " ms\n";
  std::cout << "Triple pointer time : " << time2.count() << " ms\n";

  if (time1.count() > 0) {
    double ratio = time2.count() / time1.count();
    std::cout << "-> Overhead ratio   : " << ratio << "x slower\n";
  }
}

int main() {
  benchmarkTriplePointer();
  return 0;
}