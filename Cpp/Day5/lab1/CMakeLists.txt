cmake_minimum_required(VERSION 3.10)
project(Day5_ControlFlow)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day5 main.cpp)

# -O2 is extremely important here to measure true CPU branch prediction speed
# without the noise of unoptimized memory access overhead.
target_compile_options(day5 PRIVATE
        -Wall -Wextra -Wpedantic
        -O2
)