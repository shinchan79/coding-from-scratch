//
// Created by yentrinh on 27/8/26.
//
#include <iostream>

void good_swap(int& x, int& y) {
  int temp = x;
  x = y;
  y = temp;
}

void bad_swap(int x, int y) {
  std::cout << "  [bad_swap] Address of copy x: " << &x << "\n";
  std::cout << "  [bad_swap] Address of copy y: " << &y << "\n";

  int temp = x;
  x = y;
  y = temp;
}

int main() {
  // --- TASK 1: L-value vs R-value ---
  int a = 10;
  std::cout << "Address of a: " << &a << "\n";

  // Uncommenting below lines will cause compilation errors
  // std::cout << &10;      // Error: 10 is an r-value
  // std::cout << &(a + 5); // Error: (a + 5) is an r-value

  // --- TASK 2: Pass-by-reference ---
  int m = 5, n = 10;
  good_swap(m, n);
  std::cout << "After good_swap - m: " << m << ", n: " << n << "\n\n";

  // good_swap(m, 20);      // Error: 20 is an r-value

  // --- TASK 3: Pass-by-value ---
  int x_original = 100, y_original = 200;
  std::cout << "[main] Address of x_original: " << &x_original << "\n";
  std::cout << "[main] Address of y_original: " << &y_original << "\n";

  bad_swap(x_original, y_original);

  std::cout << "After bad_swap - x_original: " << x_original
            << ", y_original: " << y_original << "\n";

  return 0;
}
