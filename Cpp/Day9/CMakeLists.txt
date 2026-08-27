cmake_minimum_required(VERSION 3.10)
project(Day9_C_Arrays)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day9 main.cpp)

# -O2 is mandatory for realistic cache performance metrics
target_compile_options(day9 PRIVATE
        -Wall -Wextra -Wpedantic
        -O2
        -fsanitize=address,undefined
)
target_link_options(day9 PRIVATE
        -fsanitize=address,undefined
)