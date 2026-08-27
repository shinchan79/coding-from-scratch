//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <utility> // Required for std::move

// === 1. Wrapper Design (Template & RAII) ===
template <typename T>
class MyUniquePtr {
private:
    T* ptr;

public:
    // Explicit constructor prevents implicit conversion from raw pointer
    explicit MyUniquePtr(T* p = nullptr) : ptr(p) {
        std::cout << "  [MyUniquePtr] Taking ownership of memory at " << (void*)ptr << '\n';
    }

    // RAII: The destructor automatically cleans up the Heap memory
    ~MyUniquePtr() {
        if (ptr) {
            std::cout << "  [MyUniquePtr] Automatically deleting memory at " << (void*)ptr << '\n';
            delete ptr;
        }
    }

    // === 2. Anti-Copy Mechanism ===
    // We explicitly delete the copy constructor and copy assignment operator.
    // Unique ownership means only ONE pointer can own the memory at a time.
    MyUniquePtr(const MyUniquePtr&) = delete;
    MyUniquePtr& operator=(const MyUniquePtr&) = delete;

    // === 3. Move Semantics (Transfer of Ownership) ===
    // Steals the memory from 'other' and leaves 'other' empty (nullptr).
    MyUniquePtr(MyUniquePtr&& other) noexcept {
        ptr = other.ptr;
        other.ptr = nullptr;
        std::cout << "  [MyUniquePtr] Move constructor transferred ownership.\n";
    }

    MyUniquePtr& operator=(MyUniquePtr&& other) noexcept {
        if (this != &other) { // Prevent self-assignment
            delete ptr;       // Clean up current memory before taking new ownership
            ptr = other.ptr;
            other.ptr = nullptr;
            std::cout << "  [MyUniquePtr] Move assignment transferred ownership.\n";
        }
        return *this;
    }

    // === 4. Pointer Interface Overloads ===
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    // Allows the pointer to be checked in an if-statement (if (ptr) { ... })
    explicit operator bool() const { return ptr != nullptr; }

    // === 5. Utility Functions ===
    T* get() const { return ptr; }

    T* release() {
        T* temp = ptr;
        ptr = nullptr; // Surrender ownership without deleting
        return temp;
    }

    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
};

// --- Testing the Mini Project ---

struct Entity {
    int id;
    Entity(int i) : id(i) { std::cout << "    [+] Entity " << id << " created.\n"; }
    ~Entity() { std::cout << "    [-] Entity " << id << " destroyed.\n"; }
    void process() { std::cout << "    Entity " << id << " is processing data...\n"; }
};

// Verifying Day 13 Fix: Exception Safety
void solveExceptionLeak() {
    std::cout << "\n=== Solving Day 13 Exception Leak ===\n";

    // The smart pointer is created on the STACK, holding a pointer to the HEAP.
    MyUniquePtr<Entity> safePtr(new Entity(42));

    safePtr->process();

    try {
        std::cout << "  [!] Simulating an unexpected system crash (Exception)...\n";
        throw std::runtime_error("Network timeout!");

        // If this were a raw pointer, skipping the 'delete' below would cause a leak.
        // delete rawPtr; <- We don't need this anymore!
    } catch (const std::exception& e) {
        std::cout << "  [!] Caught: " << e.what() << '\n';
        // As control leaves the try block, the Stack Unwinding process automatically
        // destroys 'safePtr', which in turn deletes the Entity safely.
    }

    std::cout << "  -> Exiting function. Memory is already clean.\n";
}

// Verifying Transfer of Ownership
void demonstrateOwnershipTransfer() {
    std::cout << "\n=== Transfer of Ownership ===\n";
    MyUniquePtr<Entity> ptr1(new Entity(99));

    // COMPILER ERROR if uncommented:
    // MyUniquePtr<Entity> ptr2 = ptr1;

    // We must explicitly use std::move to transfer ownership
    MyUniquePtr<Entity> ptr2 = std::move(ptr1);

    if (!ptr1) {
        std::cout << "  ptr1 is now empty (null).\n";
    }
    if (ptr2) {
        std::cout << "  ptr2 is the new owner.\n";
        ptr2->process();
    }
}

int main() {
    solveExceptionLeak();
    demonstrateOwnershipTransfer();

    std::cout << "\nProgram finished. Run 'valgrind ./day15' to verify 0 bytes lost.\n";
    return 0;
}