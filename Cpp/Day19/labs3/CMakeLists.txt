cmake_minimum_required(VERSION 3.10)
project(Day19_VectorMoveLab)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(vector_move_lab main.cpp)

target_compile_options(vector_move_lab PRIVATE
        -Wall -Wextra -Wpedantic
        -O2
        -fsanitize=address,undefined
)
target_link_options(vector_move_lab PRIVATE
        -fsanitize=address,undefined
)