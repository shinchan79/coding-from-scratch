#include <iostream>
#include <typeinfo>

bool sideEffect() {
  std::cout << "Side effect executed!\n";
  return true;
}

int main() {
  // 1. Bitwise optimization
  int value = 15;
  int mulByTwo = value << 1;
  int divByTwo = value >> 1;
  bool isOdd = value & 1;

  std::cout << "15 * 2 = " << mulByTwo << '\n';
  std::cout << "15 / 2 = " << divByTwo << '\n';
  std::cout << "Is 15 odd? " << std::boolalpha << isOdd << "\n\n";

  // XOR swap
  int x = 5, y = 9;
  x ^= y;
  y ^= x;
  x ^= y;
  std::cout << "XOR Swap: x = " << x << ", y = " << y << "\n\n";

  // 2. Short-circuit evaluation
  // [[maybe_unused]] tells the compiler we intentionally ignore these variables
  [[maybe_unused]] bool shortCircuitAnd = false && sideEffect();
  [[maybe_unused]] bool shortCircuitOr = true || sideEffect();

  // 3. Type promotion
  char c1 = 10;
  char c2 = 20;
  auto result = c1 + c2;

  std::cout << "Type of c1: " << typeid(c1).name() << '\n';
  std::cout << "Type of result: " << typeid(result).name() << '\n';

  return 0;
}