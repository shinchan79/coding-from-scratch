//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
// 1. Pre-increment vs Post-increment optimization
class IteratorMock {
private:
  int value;
public:
  explicit IteratorMock(int v) : value(v) {}

  // Copy constructor to track overhead
  IteratorMock(const IteratorMock& other) {
    value = other.value;
    std::cout << "-> Overhead: Copy constructor called!\n";
  }

  // Pre-increment (++i): Returns reference, no temporary copy
  IteratorMock& operator++() {
    ++value;
    return *this;
  }

  // Post-increment (i++): Returns by value, requires a temporary copy
  IteratorMock operator++(int) {
    IteratorMock temp = *this;
    ++value;
    return temp;
  }

  int get() const { return value; }
};

// 2. constexpr optimization
// This function can be evaluated completely at compile-time
constexpr int computeFactorial(int n) {
  return (n <= 1) ? 1 : (n * computeFactorial(n - 1));
}

int main() {
  std::cout << "=== 1. ++i vs i++ ===\n";
  IteratorMock it(0);

  std::cout << "Executing ++it (Pre-increment):\n";
  ++it;

  std::cout << "Executing it++ (Post-increment):\n";
  it++;

  std::cout << "\n=== 2. constexpr ===\n";
  // fact5 is calculated during compilation, not at runtime
  constexpr int fact5 = computeFactorial(5);

  // static_assert guarantees compile-time evaluation.
  // If it fails, the code won't even build.
  static_assert(fact5 == 120, "Compile-time calculation failed!");

  std::cout << "Factorial of 5: " << fact5 << " (Zero CPU cycles spent at runtime)\n";

  return 0;
}