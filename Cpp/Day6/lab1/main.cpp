//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <string>

// 1. Declaration (Prototype)
// Function signature: process(int, double)
void process(int a, double b);

// 2. Overloading
// C++ uses "Name Mangling" to encode parameter types into the function name at compile time.
void printData(int x) {
  std::cout << "Integer version called: " << x << '\n';
}

void printData(double x) {
  std::cout << "Double version called: " << x << '\n';
}

void printData(const std::string& str) {
  std::cout << "String version called: " << str << '\n';
}

// 3. Default Arguments
// The compiled machine code only has ONE function taking exactly 3 arguments.
void connect(const std::string& ip, int port = 80, int timeout = 3000) {
  std::cout << "Connecting to " << ip << ":" << port << " (Timeout: " << timeout << "ms)\n";
}

int main() {
  std::cout << "=== 1. Declaration vs Definition ===\n";
  process(10, 3.14);

  std::cout << "\n=== 2. Overload Resolution ===\n";
  printData(42);         // Exact match: int
  printData(3.14159);    // Exact match: double

  // float promotes to double because there is no printData(float)
  printData(5.5f);

  // const char* converts to std::string
  printData("Hello C++");

  std::cout << "\n=== 3. Default Arguments ===\n";
  // Compiler injects missing arguments at the call site.

  // Assembly: call connect("192.168.1.1", 80, 3000)
  connect("192.168.1.1");

  // Assembly: call connect("10.0.0.1", 443, 3000)
  connect("10.0.0.1", 443);

  return 0;
}

// 1. Definition
void process(int a, double b) {
  std::cout << "Processing data: " << a << " and " << b << '\n';
}