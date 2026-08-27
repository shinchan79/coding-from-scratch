cmake_minimum_required(VERSION 3.10)
project(Day8_Indirection)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day8_indirection main.cpp)

# -O2 is required to measure realistic execution time.
target_compile_options(day8_indirection PRIVATE
        -Wall -Wextra -Wpedantic
        -O2
)