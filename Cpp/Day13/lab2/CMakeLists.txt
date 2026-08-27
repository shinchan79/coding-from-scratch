cmake_minimum_required(VERSION 3.10)
project(Day13_Exceptions_Arrays)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day13_part2 main.cpp)

# The -g flag and ASan are strictly required to pinpoint exactly
# where the allocation occurred before the exception was thrown.
target_compile_options(day13_part2 PRIVATE
        -Wall -Wextra -Wpedantic
        -g
        -fsanitize=address,undefined
)
target_link_options(day13_part2 PRIVATE
        -fsanitize=address,undefined
)