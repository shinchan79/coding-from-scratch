#include <iostream>
#include <chrono>
#include <cstdlib>

struct Entity {
    int id;

    Entity() : id(42) {
        std::cout << "  [+] Constructor called. ID initialized to " << id << '\n';
    }

    ~Entity() {
        std::cout << "  [-] Destructor called.\n";
    }
};

// 1. malloc/free vs new/delete
void compareAllocators() {
    std::cout << "=== 1. malloc/free vs new/delete ===\n";

    std::cout << "[malloc/free]:\n";
    // malloc only asks the OS for raw memory bytes. It does NOT call the C++ constructor.
    Entity* e1 = static_cast<Entity*>(std::malloc(sizeof(Entity)));
    std::cout << "  Garbage ID: " << e1->id << " (Uninitialized raw memory)\n";
    std::free(e1); // Does NOT call the destructor. Memory is just returned.

    std::cout << "\n[new/delete]:\n";
    // new asks for memory AND calls the constructor immediately.
    Entity* e2 = new Entity();
    delete e2; // Calls the destructor first, then frees the memory.
}

// 2. Heap vs Stack Overhead Benchmark
void benchmarkOverhead() {
    std::cout << "\n=== 2. Allocation Overhead Benchmark (10M Iterations) ===\n";
    constexpr int ITERATIONS = 10'000'000;

    // Test A: Stack Allocation
    auto startStack = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERATIONS; ++i) {
        // CPU merely subtracts 4 bytes from the Stack Pointer register (1 clock cycle).
        volatile int stackVar = i;
        (void)stackVar;
    }
    auto endStack = std::chrono::high_resolution_clock::now();

    // Test B: Heap Allocation
    auto startHeap = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERATIONS; ++i) {
        // OS must lock memory, traverse the Freelist/Bitmap to find a suitable gap,
        // update metadata, and return the address (hundreds of clock cycles).
        volatile int* heapVar = new int(i);
        delete heapVar;
    }
    auto endHeap = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> timeStack = endStack - startStack;
    std::chrono::duration<double, std::milli> timeHeap = endHeap - startHeap;

    std::cout << "Stack allocation time: " << timeStack.count() << " ms\n";
    std::cout << "Heap allocation time : " << timeHeap.count() << " ms\n";

    if (timeStack.count() > 0) {
        double ratio = timeHeap.count() / timeStack.count();
        std::cout << "-> Heap is ~" << static_cast<int>(ratio) << "x slower.\n";
    }
}

int main() {
    compareAllocators();
    benchmarkOverhead();
    return 0;
}