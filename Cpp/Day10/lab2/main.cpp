//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <cstddef> // Required for offsetof

// 1. Bad Order: Mixing small and large types randomly
struct BadOrder {
  char a;     // 1 byte
  double b;   // 8 bytes
  short c;    // 2 bytes
  int d;      // 4 bytes
  char e;     // 1 byte
};

// 2. Good Order: Largest to smallest
struct GoodOrder {
  double b;   // 8 bytes
  int d;      // 4 bytes
  short c;    // 2 bytes
  char a;     // 1 byte
  char e;     // 1 byte
};

int main() {
  std::cout << "=== 1. Struct Size Comparison ===\n";
  std::cout << "Alignment requirement (max member size): " << alignof(double) << " bytes\n\n";

  std::cout << "Size of BadOrder : " << sizeof(BadOrder) << " bytes\n";
  std::cout << "Size of GoodOrder: " << sizeof(GoodOrder) << " bytes\n\n";

  std::cout << "=== 2. Memory Layout Analysis (offsetof) ===\n";

  std::cout << "[BadOrder Layout]\n";
  std::cout << "char a   offset: " << offsetof(BadOrder, a) << '\n';
  // 7 bytes of wasted padding here!
  std::cout << "double b offset: " << offsetof(BadOrder, b) << '\n';
  std::cout << "short c  offset: " << offsetof(BadOrder, c) << '\n';
  // 2 bytes of wasted padding here!
  std::cout << "int d    offset: " << offsetof(BadOrder, d) << '\n';
  std::cout << "char e   offset: " << offsetof(BadOrder, e) << '\n';
  // 7 more bytes of padding at the end to make total size a multiple of 8!

  std::cout << "\n[GoodOrder Layout]\n";
  std::cout << "double b offset: " << offsetof(GoodOrder, b) << '\n';
  std::cout << "int d    offset: " << offsetof(GoodOrder, d) << '\n';
  std::cout << "short c  offset: " << offsetof(GoodOrder, c) << '\n';
  std::cout << "char a   offset: " << offsetof(GoodOrder, a) << '\n';
  std::cout << "char e   offset: " << offsetof(GoodOrder, e) << '\n';
  std::cout << "-> Zero internal padding. 100% memory efficiency.\n";

  return 0;
}