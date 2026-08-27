cmake_minimum_required(VERSION 3.10)
project(Day18_CopySemantics)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day18 main.cpp)

target_compile_options(day18 PRIVATE
        -Wall -Wextra -Wpedantic
        -fsanitize=address,undefined
)
target_link_options(day18 PRIVATE
        -fsanitize=address,undefined
)