cmake_minimum_required(VERSION 3.10)
project(Day7_Summary_Strategy)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day7_summary main.cpp)

# -O2 is mandatory here to enable Tail Call Optimization and see real cache performance
target_compile_options(day7_summary PRIVATE
        -Wall -Wextra -Wpedantic
        -O2
)