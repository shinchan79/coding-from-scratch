//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <cstddef> // Required for offsetof

// Challenge: Design a struct with 5 distinct data types
// Types: double (8), int (4), short (2), char (1), bool (1)

// 1. Inefficient Design: Random order causes massive padding
struct BadStruct {
    char a;     // 1 byte
                // 7 bytes padding inserted here by compiler
    double b;   // 8 bytes
    short c;    // 2 bytes
                // 2 bytes padding inserted here
    int d;      // 4 bytes
    bool e;     // 1 byte
                // 7 bytes padding at the end to align the whole struct to 8 bytes
}; // Total size: 32 bytes

// 2. Optimized Design: Ordered from largest to smallest alignment
struct GoodStruct {
    double b;   // 8 bytes
    int d;      // 4 bytes
    short c;    // 2 bytes
    char a;     // 1 byte
    bool e;     // 1 byte
                // Total is exactly 16 bytes. Zero padding required!
}; // Total size: 16 bytes

int main() {
    std::cout << "=== 1. Alignment Requirements (alignof) ===\n";
    std::cout << "alignof(double): " << alignof(double) << " bytes\n";
    std::cout << "alignof(int)   : " << alignof(int) << " bytes\n";
    std::cout << "alignof(short) : " << alignof(short) << " bytes\n";
    std::cout << "alignof(char)  : " << alignof(char) << " bytes\n";
    std::cout << "alignof(bool)  : " << alignof(bool) << " bytes\n\n";

    std::cout << "=== 2. Struct Size Comparison ===\n";
    std::cout << "BadStruct Size : " << sizeof(BadStruct) << " bytes\n";
    std::cout << "GoodStruct Size: " << sizeof(GoodStruct) << " bytes\n\n";

    std::cout << "=== 3. Memory Layout Analysis (offsetof) ===\n";
    std::cout << "[BadStruct Layout]\n";
    std::cout << "Offset a (char)  : " << offsetof(BadStruct, a) << '\n';
    std::cout << "Offset b (double): " << offsetof(BadStruct, b) << " <- (7 bytes of padding before this!)\n";
    std::cout << "Offset c (short) : " << offsetof(BadStruct, c) << '\n';
    std::cout << "Offset d (int)   : " << offsetof(BadStruct, d) << " <- (2 bytes of padding before this!)\n";
    std::cout << "Offset e (bool)  : " << offsetof(BadStruct, e) << '\n';

    std::cout << "\n[GoodStruct Layout]\n";
    std::cout << "Offset b (double): " << offsetof(GoodStruct, b) << '\n';
    std::cout << "Offset d (int)   : " << offsetof(GoodStruct, d) << '\n';
    std::cout << "Offset c (short) : " << offsetof(GoodStruct, c) << '\n';
    std::cout << "Offset a (char)  : " << offsetof(GoodStruct, a) << '\n';
    std::cout << "Offset e (bool)  : " << offsetof(GoodStruct, e) << '\n';
    std::cout << "-> Zero internal padding. 100% memory efficiency.\n";

    return 0;
}