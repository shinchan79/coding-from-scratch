cmake_minimum_required(VERSION 3.10)
project(Day4_Practice)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day4_practice main.cpp)

# Note: Added -O2 for benchmarking. Without optimization, the time difference
# is just the overhead of debug instructions, not the actual CPU math speed.
target_compile_options(day4_practice PRIVATE
        -Wall -Wextra -Wpedantic
        -O2
)