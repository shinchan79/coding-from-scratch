cmake_minimum_required(VERSION 3.10)
project(Day16_DateClass)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day16_date main.cpp)

target_compile_options(day16_date PRIVATE
        -Wall -Wextra -Wpedantic
        -fsanitize=address,undefined
)
target_link_options(day16_date PRIVATE
        -fsanitize=address,undefined
)