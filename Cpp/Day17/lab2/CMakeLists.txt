cmake_minimum_required(VERSION 3.10)
project(Day17_Destructors_Lifecycle)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day17_destructors main.cpp)

target_compile_options(day17_destructors PRIVATE
        -Wall -Wextra -Wpedantic
        -fsanitize=address,undefined
)
target_link_options(day17_destructors PRIVATE
        -fsanitize=address,undefined
)