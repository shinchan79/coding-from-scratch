//
// Created by yentrinh on 27/8/26.
//
#include <iostream>
#include <string>
#include "Timer.h"

class ILogger {
public:
  virtual ~ILogger() = default;
  virtual void log(const std::string& message) = 0;
};

class ConsoleLogger : public ILogger {
public:
  void log(const std::string& message) override {
    std::cout << "  [Console] " << message << '\n';
  }
};

class NetworkLogger : public ILogger {
public:
  void log(const std::string& message) override {
    std::cout << "  [Network] Sending over TCP: " << message << '\n';
  }
};

void processBusinessLogic(ILogger& logger) {
  logger.log("Business logic started...");
  // ... doing some heavy work ...
  logger.log("Business logic finished.");
}


int main() {
  std::cout << "=== 1. Interface Class ===\n";
  ConsoleLogger console;
  NetworkLogger net;

  std::cout << "Running with Console:\n";
  processBusinessLogic(console);

  std::cout << "\nRunning with Network:\n";
  processBusinessLogic(net);


  std::cout << "\n=== 2. Pimpl Idiom ===\n";
  Timer t;
  t.start();

  for(volatile int i = 0; i < 20'000'000; ++i) {}

  t.stop();
  t.printTime();

  return 0;
}