cmake_minimum_required(VERSION 3.10)
project(DebuggerHexLab)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CRITICAL: -g adds debug symbols, -O0 disables optimizations
add_compile_options(-g -O0)

add_executable(app_debug main.cpp)