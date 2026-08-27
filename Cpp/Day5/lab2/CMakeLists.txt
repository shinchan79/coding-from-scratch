cmake_minimum_required(VERSION 3.10)
project(Day5_Loops)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day5_part2 main.cpp)
target_compile_options(day5_part2 PRIVATE
        -Wall -Wextra -Wpedantic
        -O2
)