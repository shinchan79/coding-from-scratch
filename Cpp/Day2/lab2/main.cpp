//
// Created by yentrinh on 26/8/26.
//
#include <iostream>
#include <cstddef> // Required for offsetof macro

// Basic example: 1 char + 1 int
struct SimpleStruct {
  char letter; // 1 byte
  // Compiler silently inserts 3 bytes of padding here
  int number;  // 4 bytes
};

// Inefficient memory layout: 12 bytes
struct BadLayout {
  char a; // 1 byte
  int b;  // 4 bytes
  char c; // 1 byte
};

// Optimized memory layout: 8 bytes
struct GoodLayout {
  int b;  // 4 bytes
  char a; // 1 byte
  char c; // 1 byte
};

int main() {
  std::cout << "=== MEMORY ALIGNMENT & PADDING ===\n\n";

  // 1. The 8-byte mystery
  std::cout << "[1. The 8-byte Mystery]\n";
  std::cout << "- Size of char: " << sizeof(char) << " byte\n";
  std::cout << "- Size of int:  " << sizeof(int) << " bytes\n";
  std::cout << "- Total size of SimpleStruct: " << sizeof(SimpleStruct)
            << " bytes (Expected 5, got 8)\n\n";

  // 2. Uncovering the hidden padding
  std::cout << "[2. Memory Layout Analysis]\n";
  std::cout << "- Offset of 'letter' (char): " << offsetof(SimpleStruct, letter) << " bytes\n";
  std::cout << "- Offset of 'number' (int):  " << offsetof(SimpleStruct, number) << " bytes\n";
  std::cout << "  *(Notice the 3-byte gap between offset 1 and 4)*\n\n";

  // 3. Applying Data-Oriented Design (DOD)
  std::cout << "[3. Struct Optimization]\n";
  std::cout << "- Size of BadLayout (char -> int -> char):  " << sizeof(BadLayout) << " bytes\n";
  std::cout << "- Size of GoodLayout (int -> char -> char): " << sizeof(GoodLayout) << " bytes\n";

  return 0;
}