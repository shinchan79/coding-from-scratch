//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <string>

// Mock object to track copy overhead
struct BigData {
    std::string content;

    explicit BigData(const std::string& str) : content(str) {}

    // Copy constructor logs to console when invoked
    BigData(const BigData& other) {
        content = other.content;
        std::cout << "  [Warning] Costly copy performed for: " << content << '\n';
    }
};

// 1. Pass-by-value (T)
// Good for primitive types (int, double, bool) that fit in CPU registers.
void processSmall(int value) {
    value += 1;
}

// BAD: Causes an expensive deep copy for large objects.
void processLargeByValue(BigData data) {
    std::cout << "  Doing work with: " << data.content << '\n';
}

// 2. Pass-by-const-reference (const T&)
// The Gold Standard for any object larger than a pointer (std::string, vector, struct).
// Zero copy overhead, read-only access.
void processConstRef(const BigData& data) {
    std::cout << "  Doing work with: " << data.content << " (No copy!)\n";
}

// 3. Pass-by-reference (T&)
// Use ONLY when the function explicitly needs to modify the original caller's object.
void processRef(BigData& data) {
    data.content += " -> [Processed]";
}

// 4. Pass-by-pointer (T*)
// Use instead of T& ONLY if the argument is optional (can legitimately be nullptr).
void processOptional(BigData* dataPtr) {
    if (dataPtr != nullptr) {
        std::cout << "  Valid pointer: " << dataPtr->content << '\n';
    } else {
        std::cout << "  Received nullptr, falling back to default behavior.\n";
    }
}

int main() {
    BigData payload("System Config");

    std::cout << "=== 1. Pass-by-value (Large Object) ===\n";
    processLargeByValue(payload);

    std::cout << "\n=== 2. Pass-by-const-reference (const T&) ===\n";
    processConstRef(payload);

    std::cout << "\n=== 3. Pass-by-reference (T&) ===\n";
    processRef(payload);
    std::cout << "  Original modified to: " << payload.content << '\n';

    std::cout << "\n=== 4. Pass-by-pointer (T*) ===\n";
    processOptional(&payload);    // Must pass address
    processOptional(nullptr);     // Optionality demonstrated

    return 0;
}