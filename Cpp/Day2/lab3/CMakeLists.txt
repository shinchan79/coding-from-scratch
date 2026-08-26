cmake_minimum_required(VERSION 3.10)
project(StaticVsDynamicLab)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable optimization flag for benchmarking (-O2)
add_compile_options(-O2)

add_executable(app_benchmark main.cpp)