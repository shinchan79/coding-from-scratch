//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <string>
#include <cstdint>
#include <iomanip>

int main() {
  std::cout << "=== Small String Optimization (SSO) ===\n";

  std::string str;

  std::cout << "Size of std::string object: " << sizeof(std::string) << " bytes\n";
  std::cout << "Address of 'str' on STACK : " << static_cast<void*>(&str) << "\n\n";

  size_t sso_threshold = 0;
  bool threshold_found = false;

  for (size_t i = 1; i <= 32; ++i) {
    str.push_back('x');

    // str.data() returns the memory address where the actual characters are stored
    const void* data_addr = static_cast<const void*>(str.data());

    // Calculate the absolute distance in memory between the string object and its character data
    uintptr_t obj_addr_val = reinterpret_cast<uintptr_t>(&str);
    uintptr_t data_addr_val = reinterpret_cast<uintptr_t>(data_addr);
    uintptr_t diff = (obj_addr_val > data_addr_val) ? (obj_addr_val - data_addr_val) : (data_addr_val - obj_addr_val);

    // If the data address is extremely close to the object's address (less than the size of the object),
    // it means the text payload is stored INSIDE the object itself (on the Stack).
    bool is_on_stack = (diff < sizeof(std::string));

    std::cout << "Len: " << std::setw(2) << str.length()
              << " | Cap: " << std::setw(2) << str.capacity()
              << " | Data Addr: " << data_addr;

    if (is_on_stack) {
      std::cout << "  [STACK (SSO)]\n";
    } else {
      std::cout << "  [HEAP]\n";
      if (!threshold_found) {
        sso_threshold = i - 1;
        threshold_found = true;
      }
    }
  }

  std::cout << "\n-> Compiler's SSO Threshold: " << sso_threshold << " characters.\n";

  return 0;
}