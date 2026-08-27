cmake_minimum_required(VERSION 3.10)
project(Day18_RuleOfThree)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day18_rule_of_three main.cpp)

target_compile_options(day18_rule_of_three PRIVATE
        -Wall -Wextra -Wpedantic
        -fsanitize=address,undefined
)
target_link_options(day18_rule_of_three PRIVATE
        -fsanitize=address,undefined
)