//
// Created by yentrinh on 26/8/26.
//
#include <fmt/core.h>
#include <string>
int main() {
  // Use fmt::print instead of std::cout
  fmt::print("Hello, Modern C++ with fmt!\n");

  // try formatting
  std::string name = "macOS";
  int year = 2026;
  fmt::print("Running on {} at {}.\n", name, year);

  return 0;
}