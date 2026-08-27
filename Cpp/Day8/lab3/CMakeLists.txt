cmake_minimum_required(VERSION 3.10)
project(Day8_TriplePointerLab)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day8_lab main.cpp)

target_compile_options(day8_lab PRIVATE
        -Wall -Wextra -Wpedantic
        -O2
)