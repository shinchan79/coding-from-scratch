//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <thread>
#include <vector>

// Heavy object simulating a complex global state or configuration
class ComplexGlobalState {
public:
    ComplexGlobalState() {
        std::cout << "  [Init] ComplexGlobalState constructed on Thread ID: "
                  << std::this_thread::get_id() << '\n';
    }

    ~ComplexGlobalState() {
        std::cout << "  [Destroy] ComplexGlobalState destroyed.\n";
    }

    void doWork() {
        std::cout << "  [Work] Processing state...\n";
    }
};

// 1. Thread-Local Storage (TLS): Each thread gets its own isolated instance.
// Eliminates data races and mutex overhead entirely in multi-threaded contexts.
ComplexGlobalState& getThreadLocalInstance() {
    thread_local ComplexGlobalState tlsInstance;
    return tlsInstance;
}

// 2. Local Static Object (Meyers' Singleton pattern style initialization)
// Thread-safe initialization guaranteed by C++11 and later standards.
ComplexGlobalState& getLocalStaticInstance() {
    static ComplexGlobalState staticInstance;
    return staticInstance;
}

void workerTask(int threadId) {
    std::cout << "Worker thread " << threadId << " started.\n";

    // Accessing thread-local storage (isolated per thread)
    ComplexGlobalState& tlsRef = getThreadLocalInstance();
    tlsRef.doWork();

    // Accessing local static storage (shared across threads, thread-safe init)
    ComplexGlobalState& staticRef = getLocalStaticInstance();
    staticRef.doWork();
}

int main() {
    std::cout << "=== Optimization Insight: Static & Thread-Local Storage ===\n\n";

    std::cout << "1. Accessing Local Static Object for the first time:\n";
    {
        ComplexGlobalState& s = getLocalStaticInstance();
        s.doWork();
    }

    std::cout << "\n2. Spawning multiple threads to observe TLS and Static behavior:\n";
    std::vector<std::jthread> threads;
    for (int i = 1; i <= 3; ++i) {
        threads.emplace_back(workerTask, i);
    }

    // jthread automatically joins upon destruction here
    threads.clear();

    std::cout << "\nProgram ending.\n";
    return 0;
}