cmake_minimum_required(VERSION 3.10)
project(Day15_MiniProject_SmartPointer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day15 main.cpp)

# -g is strictly required for Valgrind to show exact line numbers for leaks.
# Note: AddressSanitizer (-fsanitize=address) is intentionally omitted here.
# ASan overrides the system's default memory allocator, which conflicts with Valgrind.
# To prove "Valgrind 0 bytes lost" for this lab, we must compile without ASan.
target_compile_options(day15 PRIVATE
        -Wall -Wextra -Wpedantic
        -g
)