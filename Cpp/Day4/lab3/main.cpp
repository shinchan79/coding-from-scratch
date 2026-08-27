//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <chrono>

void benchmarkBitwiseVsArithmetic() {
  constexpr int ITERATIONS = 500'000'000;

  // 'volatile' prevents the -O2 compiler from completely deleting
  // these loops (Dead Code Elimination) since the result isn't printed.
  volatile int dummy = 0;
  int num = 1024;

  // 1. Standard arithmetic division
  auto start1 = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < ITERATIONS; ++i) {
    dummy = num / 2;
  }
  auto end1 = std::chrono::high_resolution_clock::now();

  // 2. Bitwise shift division
  auto start2 = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < ITERATIONS; ++i) {
    dummy = num >> 1;
  }
  auto end2 = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double, std::milli> time1 = end1 - start1;
  std::chrono::duration<double, std::milli> time2 = end2 - start2;

  std::cout << "=== Performance Benchmark (500M iterations) ===\n";
  std::cout << "Arithmetic (num / 2) : " << time1.count() << " ms\n";
  std::cout << "Bitwise    (num >> 1): " << time2.count() << " ms\n\n";
}

void operatorPrecedenceBug() {
  std::cout << "=== Operator Precedence Bug ===\n";
  int value = 6;

  // BUG: '==' has higher precedence than '&'
  // Compiler evaluates this as: value & (1 == 0) => value & 0 => 0 (false)
  // Warning -Wparentheses will actually flag this in a real build!
  bool isEvenBuggy = value & 1 == 0;

  // FIX: Enforce correct evaluation order with parentheses
  // Evaluates as: (value & 1) == 0 => (0) == 0 => true
  bool isEvenCorrect = (value & 1) == 0;

  std::cout << "Checking if " << value << " is even:\n";
  std::cout << "Buggy   (value & 1 == 0)  : " << std::boolalpha << isEvenBuggy << '\n';
  std::cout << "Correct ((value & 1) == 0): " << isEvenCorrect << '\n';
}

int main() {
  benchmarkBitwiseVsArithmetic();
  operatorPrecedenceBug();
  return 0;
}