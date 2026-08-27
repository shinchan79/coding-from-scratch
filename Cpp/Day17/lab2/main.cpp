//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <string>

// Mock resource holder simulating files, sockets, or memory blocks
class ResourceHandle {
private:
  std::string name;

public:
  explicit ResourceHandle(std::string resName) : name(std::move(resName)) {
    std::cout << "    [+] Resource acquired: " << name << '\n';
  }

  ~ResourceHandle() {
    std::cout << "    [-] Resource cleaned up: " << name << '\n';
  }
};

// Base class to demonstrate inheritance construction/destruction order
class Base {
private:
  ResourceHandle baseRes;

public:
  Base() : baseRes("BaseResource") {
    std::cout << "  [Base] Constructor called.\n";
  }

  virtual ~Base() {
    std::cout << "  [Base] Destructor called.\n";
  }
};

// Derived class
class Derived : public Base {
private:
  ResourceHandle derivedRes;

public:
  Derived() : derivedRes("DerivedResource") {
    std::cout << "  [Derived] Constructor called.\n";
  }

  ~Derived() override {
    std::cout << "  [Derived] Destructor called.\n";
  }
};

int main() {
  std::cout << "=== 1. Initialization and Destruction Order ===\n";
  {
    std::cout << "Entering scope...\n";
    Derived obj;
    std::cout << "Exiting scope...\n";
  } // Stack unwinding triggers destructors here

  std::cout << "\n=== 2. Polymorphic Cleanup (Virtual Destructor) ===\n";
  {
    // Base pointer pointing to a Derived object on the Heap
    Base* ptr = new Derived();

    std::cout << "Deleting object through Base pointer...\n";
    // Because Base::~Base() is virtual, the Derived destructor runs first,
    // preventing resource leaks from DerivedResource.
    delete ptr;
  }

  return 0;
}