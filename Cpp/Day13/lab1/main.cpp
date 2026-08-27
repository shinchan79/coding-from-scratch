//
// Created by yentrinh on 27/8/26.
//
#include <iostream>

// 1. Memory Leak (Forgot to delete)
void causeMemoryLeak() {
  std::cout << "=== 1. Memory Leak ===\n";

  // Allocating 400 bytes on the Heap
  int* leakPtr = new int[100];
  leakPtr[0] = 42;

  std::cout << "  [!] Memory allocated but never freed.\n";

  // We exit the function without calling 'delete[] leakPtr;'.
  // The pointer 'leakPtr' is destroyed (it was on the Stack),
  // but the 400 bytes on the Heap are now unreachable orphans.
}

// 2. Dangling Pointer (Use-After-Free)
void causeDanglingPointer() {
  std::cout << "\n=== 2. Dangling Pointer ===\n";

  int* ptr = new int(99);
  delete ptr;

  // The memory is returned to the OS, but 'ptr' still remembers the old address.
  // WARNING: Uncommenting the line below will cause ASan to immediately terminate
  // the program with a "heap-use-after-free" error.

  // std::cout << "  [!] Reading freed memory: " << *ptr << '\n';

  // FIX: Cultivate the habit of nullifying pointers immediately after deletion.
  ptr = nullptr;
}

// 3. Double Free
void causeDoubleFree() {
  std::cout << "\n=== 3. Double Free ===\n";

  int* ptr = new int(100);
  delete ptr;

  // Attempting to return memory to the OS that has already been returned.
  // WARNING: Uncommenting the line below will cause ASan to immediately terminate
  // the program with a "double-free" error.

  // delete ptr;
}

int main() {
  causeMemoryLeak();
  causeDanglingPointer();
  causeDoubleFree();

  std::cout << "\nProgram finished. ASan will now print the leak report.\n";
  return 0;
}