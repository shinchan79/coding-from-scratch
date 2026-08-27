//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <vector>

// Mock large object to track constructor calls
struct BigData {
  std::vector<int> payload;

  BigData() {
    std::cout << "  [+] Default Constructor called\n";
  }

  // Copy constructor
  BigData(const BigData& other) : payload(other.payload) {
    std::cout << "  [-] Copy Constructor called (EXPENSIVE DEEP COPY!)\n";
  }

  // Move constructor
  BigData(BigData&& other) noexcept : payload(std::move(other.payload)) {
    std::cout << "  [~] Move Constructor called (Cheap transfer)\n";
  }

  // Disable assignment operators for this demonstration
  BigData& operator=(const BigData&) = delete;
  BigData& operator=(BigData&&) = delete;
};

// 1. Legacy Approach: Pass by reference (Out Parameter)
// Used heavily in C and older C++ codebases to avoid copying.
void generateLegacy(BigData& outData) {
  outData.payload = {1, 2, 3};
}

// 2. Modern Approach: Return by value
// Looks like it would cause an expensive copy, but compiler magic prevents it.
BigData generateModern() {
  BigData temp;
  temp.payload = {1, 2, 3};
  return temp;              // Named Return Value Optimization (NRVO) applies here
}

int main() {
  std::cout << "=== 1. Legacy: Out Parameter ===\n";
  // Requires pre-allocation in an uninitialized or empty state
  BigData obj1;
  generateLegacy(obj1);

  std::cout << "\n=== 2. Modern: Return by Value (RVO) ===\n";
  // Constructed directly at the call site. No copy, no move!
  BigData obj2 = generateModern();

  return 0;
}