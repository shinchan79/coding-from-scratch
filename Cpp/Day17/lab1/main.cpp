//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <string>

// Helper class to track constructor and assignment calls
struct Resource {
    std::string name;

    Resource(std::string n) : name(std::move(n)) {
        std::cout << "    [+] Resource '" << name << "' Parameterized Constructor\n";
    }

    Resource(const Resource& other) : name(other.name) {
        std::cout << "    [-] Resource '" << name << "' Copy Constructor\n";
    }

    Resource& operator=(const Resource& other) {
        name = other.name;
        std::cout << "    [~] Resource '" << name << "' Copy Assignment Operator\n";
        return *this;
    }
};

// Demonstration Class
class Player {
private:
    int id;
    std::string name;
    Resource res;

public:
    // 1. Default Constructor
    Player() : id(0), name("Guest"), res("DefaultRes") {
        std::cout << "  [Player] Default Constructor called.\n";
    }

    // 3. Explicit Constructor prevents accidental implicit conversions
    explicit Player(int pId) : id(pId), name("Bot"), res("BotRes") {
        std::cout << "  [Player] Parameterized Constructor (ID only) called.\n";
    }

    // 2. Parameterized Constructor with Member Initializer List
    Player(int pId, std::string pName, std::string resName)
        : id(pId), name(std::move(pName)), res(std::move(resName)) {
        std::cout << "  [Player] Full Parameterized Constructor called.\n";
    }

    // 4. Delegating Constructor (C++11): Delegates work to the primary constructor above
    Player(int pId, std::string pName) : Player(pId, std::move(pName), "StandardRes") {
        std::cout << "  [Player] Delegating Constructor called.\n";
    }

    void print() const {
        std::cout << "  Player ID: " << id << ", Name: " << name << ", Resource: " << res.name << "\n\n";
    }
};

// Function taking an explicit Player object to demonstrate 'explicit' safety
void processPlayer(const Player& p) {
    std::cout << "  Processing player successfully!\n";
    p.print();
}

int main() {
    std::cout << "=== 1. Default & Parameterized Constructors ===\n";
    Player p1;
    p1.print();

    Player p2(101, "Alice", "EpicSword");
    p2.print();

    std::cout << "=== 2. Delegating Constructor ===\n";
    Player p3(102, "Bob"); // Delegates to the 3-argument constructor
    p3.print();

    std::cout << "=== 3. Explicit Constructor ===\n";
    // COMPILE ERROR if uncommented:
    // Because the constructor is marked 'explicit', the compiler will NOT
    // implicitly convert integer 42 into a Player object.
    // processPlayer(42);

    // Correct way: Explicitly invoke the constructor
    processPlayer(Player(42));

    return 0;
}