cmake_minimum_required(VERSION 3.10)
project(Day12_HeapInternals)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day12_heap main.cpp)

# -O2 is required to measure the true hardware cost of allocations
target_compile_options(day12_heap PRIVATE
        -Wall -Wextra -Wpedantic
        -O2
)