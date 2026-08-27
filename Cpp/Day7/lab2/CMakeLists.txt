cmake_minimum_required(VERSION 3.10)
project(Day7_Recursion_Inlining)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day7_part2 main.cpp)

# -O2 is absolutely required here.
# Without it, Tail Call Optimization (TCO) and auto-inlining will NOT happen.
target_compile_options(day7_part2 PRIVATE
        -Wall -Wextra -Wpedantic
        -O2
)