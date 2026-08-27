cmake_minimum_required(VERSION 3.10)
project(Day14_Vector_Internals)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day14 main.cpp)

# -O2 is strictly required to measure the true hardware impact of Data Locality
target_compile_options(day14 PRIVATE
        -Wall -Wextra -Wpedantic
        -O2
)