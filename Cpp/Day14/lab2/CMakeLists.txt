cmake_minimum_required(VERSION 3.10)
project(Day14_SmallStringOptimization)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day14_sso main.cpp)

target_compile_options(day14_sso PRIVATE
        -Wall -Wextra -Wpedantic
        -O2
)