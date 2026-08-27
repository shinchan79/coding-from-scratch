cmake_minimum_required(VERSION 3.10)
project(Day10_PointerArithmetic)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day10 main.cpp)

# -O2 is mandatory here to see how the compiler truly handles loop iterations
target_compile_options(day10 PRIVATE
        -Wall -Wextra -Wpedantic
        -O2
)