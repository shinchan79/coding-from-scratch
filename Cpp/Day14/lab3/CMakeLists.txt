cmake_minimum_required(VERSION 3.10)
project(Day14_Reserve_Benchmark)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day14_reserve main.cpp)

# -O2 is strictly required to measure real allocation/memory speed
target_compile_options(day14_reserve PRIVATE
        -Wall -Wextra -Wpedantic
        -O2
)