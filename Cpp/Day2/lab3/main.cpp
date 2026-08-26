//
// Created by yentrinh on 26/8/26.
//
#include <iostream>
#include <chrono>
#include <variant>

// Simulate a dynamic variable like in Python or JavaScript
// It can hold either an integer or a double at runtime.
using DynamicVar = std::variant<int, double>;

int main() {
    std::cout << "=== STATIC VS DYNAMIC TYPING BENCHMARK ===\n\n";

    // Use volatile to prevent the compiler from optimizing the entire loop into a single mathematical formula
    volatile int iterations = 50000000;

    // ---------------------------------------------------------
    // 1. STATIC TYPING (Native C++)
    // ---------------------------------------------------------
    auto startStatic = std::chrono::high_resolution_clock::now();

    long long staticSum = 0;
    for (int i = 0; i < iterations; ++i) {
        // The compiler knows EXACTLY that both are integers.
        // It maps directly to a single CPU instruction (e.g., ADD).
        staticSum += i;
    }

    auto endStatic = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> staticTime = endStatic - startStatic;

    // ---------------------------------------------------------
    // 2. DYNAMIC TYPING SIMULATION (Interpreter overhead)
    // ---------------------------------------------------------
    auto startDynamic = std::chrono::high_resolution_clock::now();

    DynamicVar dynamicSum = 0;
    for (int i = 0; i < iterations; ++i) {
        DynamicVar dynamicI = i;

        // At runtime, the "interpreter" MUST check the data type before calculating.
        // This is exactly what Python/JS does under the hood.
        if (std::holds_alternative<int>(dynamicSum) && std::holds_alternative<int>(dynamicI)) {
            dynamicSum = std::get<int>(dynamicSum) + std::get<int>(dynamicI);
        }
        else if (std::holds_alternative<double>(dynamicSum) && std::holds_alternative<double>(dynamicI)) {
            dynamicSum = std::get<double>(dynamicSum) + std::get<double>(dynamicI);
        }
    }

    auto endDynamic = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> dynamicTime = endDynamic - startDynamic;

    // ---------------------------------------------------------
    // 3. RESULTS REPORT
    // ---------------------------------------------------------
    std::cout << "[Results]\n";
    std::cout << "- Static Typing Time:  " << staticTime.count() << " ms\n";
    std::cout << "- Dynamic Typing Time: " << dynamicTime.count() << " ms\n\n";

    double ratio = dynamicTime.count() / staticTime.count();
    std::cout << "=> CONCLUSION: Static typing is roughly " << ratio << "x faster!\n";

    return 0;
}
