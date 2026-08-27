cmake_minimum_required(VERSION 3.10)
project(Day11_HeapFragmentation)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day11 main.cpp)

# ASan is highly recommended when playing with raw new/delete
target_compile_options(day11 PRIVATE
        -Wall -Wextra -Wpedantic
        -O2
        -fsanitize=address,undefined
)
target_link_options(day11 PRIVATE
        -fsanitize=address,undefined
)