cmake_minimum_required(VERSION 3.10)
project(UniformInitLab)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable strict warnings
add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(app_init main.cpp)