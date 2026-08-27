cmake_minimum_required(VERSION 3.10)
project(Day12_StackVsHeap_1M)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day12_lab main.cpp)

# -O2 is required to measure the true hardware cost of allocations.
target_compile_options(day12_lab PRIVATE
        -Wall -Wextra -Wpedantic
        -O2
)