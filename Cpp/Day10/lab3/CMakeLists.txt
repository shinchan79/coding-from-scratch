cmake_minimum_required(VERSION 3.10)
project(Day10_StructOptimization)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day10_lab main.cpp)

target_compile_options(day10_lab PRIVATE
        -Wall -Wextra -Wpedantic
)