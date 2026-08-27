//
// Created by yentrinh on 27/8/26.
//
#include "Timer.h"
#include <iostream>
#include <chrono>

class Timer::Impl {
public:
  std::chrono::high_resolution_clock::time_point startTime;
  std::chrono::high_resolution_clock::time_point endTime;

  void start() {
    startTime = std::chrono::high_resolution_clock::now();
    std::cout << "  [Timer] Started.\n";
  }

  void stop() {
    endTime = std::chrono::high_resolution_clock::now();
    std::cout << "  [Timer] Stopped.\n";
  }

  void printTime() const {
    std::chrono::duration<double, std::milli> ms = endTime - startTime;
    std::cout << "  [Timer] Elapsed: " << ms.count() << " ms\n";
  }
};

Timer::Timer() : pimpl(std::make_unique<Impl>()) {}
Timer::~Timer() = default;

Timer::Timer(Timer&&) noexcept = default;
Timer& Timer::operator=(Timer&&) noexcept = default;   // <-- note the fix below

void Timer::start() { pimpl->start(); }
void Timer::stop() { pimpl->stop(); }
void Timer::printTime() const { pimpl->printTime(); }