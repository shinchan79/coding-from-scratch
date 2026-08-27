cmake_minimum_required(VERSION 3.10)
project(Day17_OptimizationInsights)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day17_optimization main.cpp)

target_compile_options(day17_optimization PRIVATE
        -Wall -Wextra -Wpedantic
        -fsanitize=address,undefined,thread
)
target_link_options(day17_optimization PRIVATE
        -fsanitize=address,undefined,thread
)