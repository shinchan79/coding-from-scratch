cmake_minimum_required(VERSION 3.10)
project(Day13_MemoryErrors)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day13 main.cpp)

# The -g flag is crucial here so ASan/Valgrind can tell you the exact line number of the leak.
target_compile_options(day13 PRIVATE
        -Wall -Wextra -Wpedantic
        -g
        -fsanitize=address,undefined
)
target_link_options(day13 PRIVATE
        -fsanitize=address,undefined
)