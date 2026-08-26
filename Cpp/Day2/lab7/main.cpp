//
// Created by yentrinh on 26/8/26.
//
#include <iostream>
#include <limits>

void triggerUninitializedVariable() {
  std::cout << "[1. Uninitialized Variable]\n";

  // We declare a variable but never assign a value to it.
  int garbageValue;

  // Printing it invokes Undefined Behavior.
  // It does NOT default to 0. It reads whatever random bits were left in RAM.
  std::cout << "- The value of uninitialized int is: " << garbageValue << "\n\n";
}

void triggerIntegerOverflow() {
  std::cout << "[2. Signed Integer Overflow]\n";

  int maxInt = std::numeric_limits<int>::max();
  std::cout << "- Current max value of int: " << maxInt << "\n";

  // Adding 1 to the maximum signed integer invokes Undefined Behavior.
  // The C++ standard assumes signed overflow NEVER happens.
  int overflowedInt = maxInt + 1;

  std::cout << "- Max int + 1 equals: " << overflowedInt << "\n";
  std::cout << "- Did it wrap to a negative number? That is UB!\n\n";
}

int main() {
  std::cout << "=== UNDEFINED BEHAVIOR (UB) LAB ===\n\n";

  triggerUninitializedVariable();
  triggerIntegerOverflow();

  return 0;
}