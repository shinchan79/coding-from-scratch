//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <new> // Required for placement new

struct Entity {
    int id;
    double value;

    Entity(int i, double v) : id(i), value(v) {
        std::cout << "  [+] Entity " << id << " constructed.\n";
    }

    ~Entity() {
        std::cout << "  [-] Entity " << id << " destroyed.\n";
    }
};

// 1. Placement New (Advanced Memory Pool)
void testPlacementNew() {
    std::cout << "=== 1. Placement New ===\n";

    // Pre-allocate a raw memory chunk on the Stack (can also be on Heap)
    constexpr int POOL_SIZE = 1024;
    alignas(Entity) char memoryPool[POOL_SIZE];

    std::cout << "  Memory pool starts at: " << (void*)memoryPool << '\n';

    // Construct objects directly inside the pre-allocated pool
    // No OS allocation overhead!
    Entity* e1 = new (memoryPool) Entity(1, 100.5);
    Entity* e2 = new (memoryPool + sizeof(Entity)) Entity(2, 200.5);

    // CRITICAL: You must manually call the destructor.
    // NEVER use 'delete e1;' because the memory was not allocated via standard 'new'.
    e2->~Entity();
    e1->~Entity();
}

// 2. Wild Pointer
void testWildPointer() {
    std::cout << "\n=== 2. Wild Pointer ===\n";

    // Uninitialized pointer points to a random garbage memory address.
    // The compiler will likely warn about this (-Wuninitialized).
    int* wildPtr;

    // DANGER: Dereferencing this causes Undefined Behavior (Crash or silent corruption)
    // *wildPtr = 42;

    std::cout << "  Wild pointer address: " << wildPtr << " (Garbage/Random)\n";
}

// 3. Dangling Pointer
void testDanglingPointer() {
    std::cout << "\n=== 3. Dangling Pointer ===\n";
    int* ptr = new int(42);

    delete ptr;
    // 'ptr' still holds the old address, but the memory is now returned to the OS.
    // It is now a Dangling Pointer.

    // DANGER: ASan will throw a "heap-use-after-free" error if you uncomment this!
    // std::cout << *ptr << '\n';

    // FIX: Always nullify after delete
    ptr = nullptr;
    std::cout << "  Memory freed and pointer safely nullified.\n";
}

// 4. Memory Leak
void testMemoryLeak() {
    std::cout << "\n=== 4. Memory Leak ===\n";
    int* leakPtr = new int(99);

    // We reassign the pointer to a new address without deleting the original memory.
    // The integer '99' is now permanently lost in the Heap (Memory Leak).
    leakPtr = new int(100);

    delete leakPtr;

    // Note: ASan will intercept program exit and print a red Memory Leak trace for '99'.
    std::cout << "  Memory leak intentionally created. Check ASan output!\n";
}

int main() {
    testPlacementNew();
    testWildPointer();
    testDanglingPointer();
    testMemoryLeak();

    return 0;
}