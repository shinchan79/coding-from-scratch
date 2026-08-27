cmake_minimum_required(VERSION 3.10)
project(Day11_ResourceManagement)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day11_resource main.cpp)

# ASan is critical here to detect leaks and use-after-free
target_compile_options(day11_resource PRIVATE
        -Wall -Wextra -Wpedantic
        -O2
        -fsanitize=address,undefined
)
target_link_options(day11_resource PRIVATE
        -fsanitize=address,undefined
)