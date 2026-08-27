#include <iostream>
#include <chrono>
#include <iomanip>

// Mock object to represent a typical entity in a system
struct GameObject {
    long long id;
    double x, y, z;

    explicit GameObject(long long i) : id(i), x(0.0), y(0.0), z(0.0) {}
};

int main() {
    constexpr int ITERATIONS = 1'000'000;
    std::cout << "=== Allocating " << ITERATIONS << " objects ===\n\n";

    // 1. Heap Allocation Benchmark
    auto startHeap = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERATIONS; ++i) {
        // OS intervention required: searches freelist, updates memory metadata
        GameObject* obj = new GameObject(i);

        // volatile prevents the compiler from optimizing the allocation away
        volatile double dummy = obj->x;
        (void)dummy;

        delete obj;
    }
    auto endHeap = std::chrono::high_resolution_clock::now();

    // 2. Stack Allocation Benchmark
    auto startStack = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERATIONS; ++i) {
        // Zero OS intervention: CPU only subtracts bytes from the Stack Pointer
        GameObject obj(i);

        volatile double dummy = obj.x;
        (void)dummy;
    } // 'obj' is automatically popped off the stack here
    auto endStack = std::chrono::high_resolution_clock::now();

    // Calculate results
    std::chrono::duration<double, std::milli> timeHeap = endHeap - startHeap;
    std::chrono::duration<double, std::milli> timeStack = endStack - startStack;

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Heap (new/delete) : " << timeHeap.count() << " ms\n";
    std::cout << "Stack (local var) : " << timeStack.count() << " ms\n";

    if (timeStack.count() > 0) {
        double ratio = timeHeap.count() / timeStack.count();
        std::cout << "-> Stack is ~" << static_cast<int>(ratio) << "x faster than Heap.\n";
    }

    return 0;
}