//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <stdexcept>

// Day class implementing strict Class Invariants (PPP - Public/Private/Protected)
class Date {
private:
    int year;
    int month;
    int day;

    // Helper: Check if a given year is a leap year
    bool isLeapYear(int y) const {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    // Helper: Return the maximum number of days in a given month and year
    int getMaxDaysInMonth(int y, int m) const {
        switch (m) {
            case 2:  return isLeapYear(y) ? 29 : 28;
            case 4:
            case 6:
            case 9:
            case 11: return 30;
            default: return 31;
        }
    }

    // Invariant validation logic: Ensures date values fall within real-world calendar rules
    bool isValid(int y, int m, int d) const {
        if (y < 1) return false;
        if (m < 1 || m > 12) return false;
        if (d < 1 || d > getMaxDaysInMonth(y, m)) return false;
        return true;
    }

public:
    // Constructor acting as the Invariant gatekeeper
    Date(int y, int m, int d) {
        if (!isValid(y, m, d)) {
            throw std::invalid_argument("Error: Invariant violated! Invalid calendar date provided.");
        }
        year = y;
        month = m;
        day = d;
    }

    // Public getters (Const correctness enforced)
    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }

    // Display helper
    void print() const {
        std::cout << year << "-"
                  << (month < 10 ? "0" : "") << month << "-"
                  << (day < 10 ? "0" : "") << day << '\n';
    }
};

int main() {
    std::cout << "=== Testing Date Class Invariants (PPP) ===\n\n";

    // Test 1: Valid Date creation
    try {
        std::cout << "Attempting to create a valid date (2026-07-13)...\n";
        Date validDate(2026, 7, 13);
        std::cout << "Success! Created date: ";
        validDate.print();
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << '\n';
    }

    std::cout << '\n';

    // Test 2: Invalid Date creation (Day 32 / Month 13)
    try {
        std::cout << "Attempting to create an invalid date (2026-13-32)...\n";
        Date invalidDate(2026, 13, 32); // Throws exception, object never constructed
        invalidDate.print();
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << '\n';
    }

    return 0;
}