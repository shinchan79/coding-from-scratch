cmake_minimum_required(VERSION 3.10)
project(CastingLab)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable strict warnings to catch implicit cast issues
add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(app_cast main.cpp)