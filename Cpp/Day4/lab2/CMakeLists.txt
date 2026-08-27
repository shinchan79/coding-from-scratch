cmake_minimum_required(VERSION 3.10)
project(Day4_ConstExpr_Opt)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day4_part2 main.cpp)

target_compile_options(day4_part2 PRIVATE
        -Wall -Wextra -Wpedantic
        -fsanitize=address,undefined
)
target_link_options(day4_part2 PRIVATE
        -fsanitize=address,undefined
)