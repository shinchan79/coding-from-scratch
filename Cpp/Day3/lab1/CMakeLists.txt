cmake_minimum_required(VERSION 3.10)
project(Day3_Lab)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(day3_lab main.cpp)
target_compile_options(day3_lab PRIVATE -Wall -Wextra -Wpedantic)