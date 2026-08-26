//
// Created by yentrinh on 26/8/26.
//
#include <iostream>

int main() {
  std::cout << "=== UNIFORM INITIALIZATION & NARROWING CONVERSION ===\n\n";

  // ---------------------------------------------------------
  // 1. Copy Initialization (=): The Silent Killer
  // ---------------------------------------------------------
  double pi = 3.14159;

  // Narrowing conversion: double to int (loses decimal part)
  int badInt = pi;

  int largeNumber = 300;
  // Narrowing conversion: int to char (overflows, char max is 127)
  char badChar = largeNumber;

  std::cout << "[Using '=' (Copy Initialization)]\n";
  std::cout << "- Original double: " << pi << " -> Converted to int: " << badInt << "\n";
  std::cout << "- Original int: " << largeNumber << " -> Converted to char: " << +badChar << "\n\n";

  // ---------------------------------------------------------
  // 2. Uniform Initialization ({}): The Strict Shield
  // ---------------------------------------------------------
  std::cout << "[Using '{}' (Uniform Initialization)]\n";
  std::cout << "- Try uncommenting lines 30 and 31 in the source code.\n";
  std::cout << "- The compiler will instantly throw an error and refuse to build!\n\n";

  // TODO: Uncomment the following two lines to see the compiler error!
  int safeInt{pi};
  char safeChar{largeNumber};

  return 0;
}