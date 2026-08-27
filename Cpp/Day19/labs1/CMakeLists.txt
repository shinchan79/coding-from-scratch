cmake_minimum_required(VERSION 3.10)
project(Day19_MoveSemantics)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day19_move main.cpp)

target_compile_options(day19_move PRIVATE
        -Wall -Wextra -Wpedantic
        -fsanitize=address,undefined
)
target_link_options(day19_move PRIVATE
        -fsanitize=address,undefined
)