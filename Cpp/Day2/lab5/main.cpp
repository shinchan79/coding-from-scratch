#include <iostream>

int main() {
    std::cout << "=== IMPLICIT VS EXPLICIT CAST & C-STYLE CAST ===\n\n";

    // ---------------------------------------------------------
    // 1. Implicit Cast: The Signed vs Unsigned Trap
    // ---------------------------------------------------------
    std::cout << "[1. Implicit Cast Warning]\n";

    int negativeValue = -1;
    unsigned int positiveValue = 1;

    // The compiler implicitly converts 'negativeValue' to unsigned int.
    // -1 as an unsigned int becomes 4294967295 (on a 32-bit system).
    if (negativeValue < positiveValue) {
        std::cout << "- Normal Math: -1 is less than 1.\n\n";
    } else {
        std::cout << "- C++ Reality: -1 is GREATER than 1 (Due to silent implicit cast!)\n\n";
    }

    // ---------------------------------------------------------
    // 2. The Danger of C-Style Cast
    // ---------------------------------------------------------
    std::cout << "[2. The C-Style Cast Brute Force]\n";

    const int readOnlyData = 42;
    const int* constPtr = &readOnlyData;

    // C-style cast SILENTLY strips away the 'const' qualifier.
    // It acts as a const_cast without telling you, breaking data protection.
    int* badPtr = (int*)constPtr;

    std::cout << "- C-style cast successfully bypassed 'const' protection.\n";
    std::cout << "- This is extremely dangerous in large codebases.\n\n";

    // ---------------------------------------------------------
    // 3. Modern C++ Explicit Cast (static_cast)
    // ---------------------------------------------------------
    std::cout << "[3. Strict Safety with static_cast]\n";
    std::cout << "- Try uncommenting line 45 in the source code.\n";
    std::cout << "- The compiler will catch the const-violation and refuse to build!\n\n";

    // double pi = 3.14;
    int safeInt = static_cast<int>(pi); // This is safe and explicit

    // TODO: Uncomment the line below to see the compiler error!
    int* safePtr = static_cast<int*>(constPtr);

    return 0;
}