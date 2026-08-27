//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <iomanip>

// 3. Constant Folding
// The compiler knows 'FACTOR' is immutable. Instead of loading it from memory,
// it hardcodes '10' directly into the assembly instruction (Constant Folding).
void computeWithConst(int val) {
    const int FACTOR = 10;
    std::cout << "Result: " << val * FACTOR << '\n';
}

int main() {
    std::cout << "=== 1. Virtual Address Space & Decoding ===\n";
    int iVal = 42;
    double dVal = 3.14159;

    int* iPtr = &iVal;
    double* dPtr = &dVal;

    // Both pointers are 8 bytes on a 64-bit system because they only store a memory address.
    std::cout << "Size of int*: " << sizeof(iPtr) << " bytes\n";
    std::cout << "Size of double*: " << sizeof(dPtr) << " bytes\n";

    // How the pointer type changes data interpretation
    void* rawAddress = &dVal;

    // Forcing the compiler to interpret the double's memory as an integer
    int* wrongInterpreter = reinterpret_cast<int*>(rawAddress);

    std::cout << "Virtual Address : " << rawAddress << '\n';
    std::cout << "Decoded as double (Correct): " << *dPtr << '\n';

    // Prints garbage because IEEE 754 floating-point bits are read as a 2's complement integer
    std::cout << "Decoded as int    (Wrong)  : " << *wrongInterpreter << "\n\n";


    std::cout << "=== 2. The 4 Const + Pointer Combinations ===\n";
    int a = 100, b = 200;

    // Type 1: Non-const pointer, Non-const data
    int* p1 = &a;
    *p1 = 101;     // OK: Data can be changed
    p1 = &b;       // OK: Pointer address can be changed

    // Type 2: Non-const pointer, CONST data (Read-only data)
    const int* p2 = &a;
    // *p2 = 102;  // ERROR: Cannot change the data through p2
    p2 = &b;       // OK: Pointer address can be changed

    // Type 3: CONST pointer, Non-const data (Read-only address)
    int* const p3 = &a;
    *p3 = 103;     // OK: Data can be changed
    // p3 = &b;    // ERROR: Cannot point to another address

    // Type 4: CONST pointer, CONST data (Read-only everything)
    const int* const p4 = &a;
    // *p4 = 104;  // ERROR
    // p4 = &b;    // ERROR

    // Suppress unused variable warnings
    (void)p1; (void)p2; (void)p3; (void)p4;
    std::cout << "Compile-time safety enforced by const combinations.\n\n";

    std::cout << "=== 3. Constant Folding ===\n";
    computeWithConst(5);

    return 0;
}