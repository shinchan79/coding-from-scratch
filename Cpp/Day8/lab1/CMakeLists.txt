cmake_minimum_required(VERSION 3.10)
project(Day8_Pointers)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day8 main.cpp)

# -O2 allows the compiler to perform Constant Folding
target_compile_options(day8 PRIVATE
        -Wall -Wextra -Wpedantic
        -O2
        -fsanitize=address,undefined
)
target_link_options(day8 PRIVATE
        -fsanitize=address,undefined
)