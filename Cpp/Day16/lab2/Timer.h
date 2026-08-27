#pragma once
#include <memory>

class Timer {
public:
  Timer();
  ~Timer();

  Timer(Timer&&) noexcept;
  Timer& operator=(Timer&&) noexcept;

  Timer(const Timer&) = delete;
  Timer& operator=(const Timer&) = delete;

  void start();
  void stop();
  void printTime() const;

private:
  class Impl;
  std::unique_ptr<Impl> pimpl;
};