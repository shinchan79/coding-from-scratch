cmake_minimum_required(VERSION 3.10)
project(Day16_Encapsulation_Invariants)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day16 main.cpp)

target_compile_options(day16 PRIVATE
        -Wall -Wextra -Wpedantic
)