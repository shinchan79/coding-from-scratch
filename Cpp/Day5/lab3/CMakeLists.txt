cmake_minimum_required(VERSION 3.10)
project(Day5_Practice)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day5_practice main.cpp)

# -O2 is mandatory here. Without it, the compiler ignores [[likely]]/[[unlikely]]
# and branch prediction overhead is drowned out by unoptimized memory access.
target_compile_options(day5_practice PRIVATE
        -Wall -Wextra -Wpedantic
        -O2
)