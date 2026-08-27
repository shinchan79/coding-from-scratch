//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <stdexcept>

// === 1. Struct vs Class ===
// In C++, the ONLY difference between struct and class is the default visibility.
struct DefaultPublic {
    // Everything is 'public' by default here.
    int data;
};

class DefaultPrivate {
    // Everything is 'private' by default here.
    int data;
public:
    void setData(int d) { data = d; }
};


// === 2. Encapsulation & Class Invariants ===
class Date {
private:
    // Compiler boundary: These variables CANNOT be accessed directly from outside.
    int year;
    int month;
    int day;

    // Helper functions hidden from the user (Implementation details)
    bool isLeapYear(int y) const {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    int daysInMonth(int y, int m) const {
        if (m == 2) return isLeapYear(y) ? 29 : 28;
        if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
        return 31;
    }

    // The Invariant check: The rules that MUST be true for a Date to exist.
    bool isValid(int y, int m, int d) const {
        if (y < 1 || m < 1 || m > 12 || d < 1) return false;
        if (d > daysInMonth(y, m)) return false;
        return true;
    }

public:
    // Constructor acts as the gatekeeper for the Invariant.
    Date(int y, int m, int d) {
        std::cout << "  [Date] Attempting to create Date: " << y << "/" << m << "/" << d << "...\n";

        if (!isValid(y, m, d)) {
            // Throwing an exception prevents the object from ever existing in an invalid state.
            throw std::invalid_argument("Invariant violation: Invalid date provided!");
        }

        year = y;
        month = m;
        day = d;
        std::cout << "  [+] Date created successfully.\n";
    }

    // Public Interface (What the user can do)
    void print() const {
        std::cout << "  Current Date: " << year << "-" << month << "-" << day << "\n";
    }
};

int main() {
    std::cout << "=== 1. Struct vs Class ===\n";
    DefaultPublic pub;
    pub.data = 42; // OK: Public by default

    DefaultPrivate priv;
    // priv.data = 42; // COMPILER ERROR: 'data' is a private member
    priv.setData(42);  // OK: Accessing through public interface

    std::cout << "\n=== 2. Encapsulation & Class Invariants ===\n";

    try {
        // Test A: Valid state
        Date validDate(2026, 7, 13);
        validDate.print();

        // Test B: Invalid state (e.g., month 13, day 32)
        // The constructor will throw, and the 'invalidDate' object will NEVER be fully constructed.
        Date invalidDate(2026, 13, 32);

        // This line will never execute because control jumps to the catch block
        invalidDate.print();

    } catch (const std::exception& e) {
        std::cout << "  [!] Exception caught: " << e.what() << "\n";
    }

    return 0;
}