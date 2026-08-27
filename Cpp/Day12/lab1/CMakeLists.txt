cmake_minimum_required(VERSION 3.10)
project(Day12_StackVsHeap)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day12 main.cpp)

# -O2 is mandatory to demonstrate true cache/register performance for the Stack
target_compile_options(day12 PRIVATE
        -Wall -Wextra -Wpedantic
        -O2
)