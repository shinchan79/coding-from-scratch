#include <iostream>
#include <limits>

int main() {
  std::cout << "=== FUNDAMENTAL TYPES IN C++ ===\n\n";
  std::cout << "[int]\n";
  std::cout << "- Size: " << sizeof(int) << " bytes\n";
  std::cout << "- Range: " << std::numeric_limits<int>::min()
            << " to " << std::numeric_limits<int>::max() << "\n\n";

  // Note: The '+' operator forces type promotion from char to int.
  // Without it, cout will try to print invisible ASCII characters instead of numbers.
  std::cout << "[char]\n";
  std::cout << "- Size: " << sizeof(char) << " bytes\n";
  std::cout << "- Range: " << +std::numeric_limits<char>::min()
            << " to " << +std::numeric_limits<char>::max() << "\n\n";

  // Note: lowest() returns the most negative value.
  // min() returns the smallest positive normalized value (closest to zero).
  std::cout << "[float]\n";
  std::cout << "- Size: " << sizeof(float) << " bytes\n";
  std::cout << "- Range: " << std::numeric_limits<float>::lowest()
            << " to " << std::numeric_limits<float>::max() << "\n\n";

  std::cout << "[double]\n";
  std::cout << "- Size: " << sizeof(double) << " bytes\n";
  std::cout << "- Range: " << std::numeric_limits<double>::lowest()
            << " to " << std::numeric_limits<double>::max() << "\n\n";

  std::cout << "[bool]\n";
  std::cout << "- Size: " << sizeof(bool) << " bytes\n";
  std::cout << "- Range: " << std::numeric_limits<bool>::min()
            << " to " << std::numeric_limits<bool>::max() << "\n\n";

  return 0;
}