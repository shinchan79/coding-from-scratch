cmake_minimum_required(VERSION 3.10)
project(Day11_VectorVsList_Copy)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day11_part2 main.cpp)

# -O2 is absolutely required to measure real CPU cache and memory speed
target_compile_options(day11_part2 PRIVATE
        -Wall -Wextra -Wpedantic
        -O2
)