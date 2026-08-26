//
// Created by yentrinh on 26/8/26.
//
#include <iostream>

int main() {
  std::cout << "=== DEBUGGER HEX VIEW LAB ===\n\n";

  // 1. A negative number (to observe Two's Complement)
  int negativeNumber = -1;

  // 2. An unsigned integer commonly used as a bitmask (e.g., in networking or graphics)
  unsigned int colorMask = 4278190080; // Represents 100% Red in ARGB format

  // 3. A floating-point number (to observe IEEE 754 encoding)
  float piFloat = 3.14159f;

  // We will set a debugger breakpoint at the line below!
  std::cout << "Variables are initialized. Please check the debugger.\n";

  return 0;
}