//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <stdexcept>

struct Entity {
    static int counter;
    int id;

    Entity() {
        id = ++counter;
        std::cout << "  [+] Entity " << id << " constructed.\n";
    }

    ~Entity() {
        std::cout << "  [-] Entity " << id << " destroyed.\n";
    }
};

int Entity::counter = 0;

// 1. Mismatched new[] and delete
void causeMismatchedDelete() {
    std::cout << "=== 1. Mismatched new[] / delete ===\n";

    // Allocates memory and calls constructor 3 times
    Entity* arr = new Entity[3];

    std::cout << "  Attempting to free...\n";

    // DANGER: Using 'delete' instead of 'delete[]' on an array.
    // It only calls the destructor for the VERY FIRST object (Entity 1).
    // The destructors for Entity 2 and 3 are NEVER called (Resource Leak).
    // Worse, on modern systems, this is Undefined Behavior and ASan will crash
    // the program with an "alloc-dealloc-mismatch" error.

    // Uncommenting the line below will cause a fatal crash:
    // delete arr;

    // FIX: Always match new[] with delete[]
    delete[] arr;
    std::cout << "  Successfully freed with delete[].\n";
}

// 2. Exception Safety Leak
void riskyProcessing() {
    std::cout << "  Executing risky process...\n";
    // Something goes wrong (e.g., file not found, network timeout)
    throw std::runtime_error("Simulated system crash!");
}

void causeExceptionLeak() {
    std::cout << "\n=== 2. Exception Safety Leak ===\n";

    // Allocate 400 bytes on the Heap
    int* buffer = new int[100];
    std::cout << "  [!] 400 bytes allocated.\n";

    try {
        riskyProcessing();

        // This line is NEVER reached because the exception abruptly
        // transfers control out of this block.
        delete[] buffer;
        std::cout << "  Buffer freed safely.\n";

    } catch (const std::exception& e) {
        std::cout << "  [!] Caught Exception: " << e.what() << '\n';
        // Control lands here. The 'buffer' pointer is about to go out of scope,
        // but the 400 bytes on the Heap were never deleted.
        // We have a Memory Leak.
    }
}

int main() {
    causeMismatchedDelete();
    causeExceptionLeak();

    std::cout << "\nProgram finished. ASan will now report the 400-byte leak.\n";
    return 0;
}