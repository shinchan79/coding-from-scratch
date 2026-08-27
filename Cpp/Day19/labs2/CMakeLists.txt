cmake_minimum_required(VERSION 3.10)
project(Day19_RuleOfFiveAndZero)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day19_rule_5_0 main.cpp)

target_compile_options(day19_rule_5_0 PRIVATE
        -Wall -Wextra -Wpedantic
        -fsanitize=address,undefined
)
target_link_options(day19_rule_5_0 PRIVATE
        -fsanitize=address,undefined
)