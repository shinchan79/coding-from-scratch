//
// Created by yentrinh on 27/8/26.
//
#include <iostream>

// 1. Calling Conventions
// Modern compilers on 64-bit systems (like your MacBook) ignore these
// because standard ABIs already use registers for arguments.
// They are mostly relevant for 32-bit x86 / Windows environments.
#if defined(_MSC_VER)
    #define CDECL_CALL __cdecl
    #define STDCALL_CALL __stdcall
    #define FASTCALL_CALL __fastcall
#elif defined(__i386__)
    #define CDECL_CALL __attribute__((cdecl))
    #define STDCALL_CALL __attribute__((stdcall))
    #define FASTCALL_CALL __attribute__((fastcall))
#else
    #define CDECL_CALL
    #define STDCALL_CALL
    #define FASTCALL_CALL
#endif

void CDECL_CALL processCdecl(int a, int b) {
    std::cout << "  cdecl (Caller cleans stack): " << a + b << '\n';
}

void STDCALL_CALL processStdcall(int a, int b) {
    std::cout << "  stdcall (Callee cleans stack): " << a + b << '\n';
}

void FASTCALL_CALL processFastcall(int a, int b) {
    std::cout << "  fastcall (Uses registers): " << a + b << '\n';
}

// 2. Stack Frame & Stack Overflow
// 'volatile' prevents the compiler from optimizing this into an infinite loop
void causeStackOverflow(int depth) {
    // Allocate ~4KB per frame to consume the stack quickly
    volatile int localArray[1000];
    localArray[0] = depth;

    // Print the memory address of the local variable.
    // You will notice the addresses getting smaller (growing downwards).
    if (depth % 500 == 0) {
        std::cout << "Depth: " << depth
                  << " | Stack Frame Address: " << (void*)&localArray[0] << '\n';
    }

    // Recursive call without a base case
    causeStackOverflow(depth + 1);
}

int main() {
    std::cout << "=== 1. Calling Conventions ===\n";
    processCdecl(10, 20);
    processStdcall(30, 40);
    processFastcall(50, 60);

    std::cout << "\n=== 2. Stack Overflow ===\n";
    std::cout << "Warning: The program is about to crash!\n";

    // Trigger the infinite recursion
    // ASan will intercept this and print a detailed stack-overflow trace.
    causeStackOverflow(1);

    return 0;
}