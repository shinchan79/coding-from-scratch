cmake_minimum_required(VERSION 3.10)
project(Day7_CallStack)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day7 main.cpp)

# Note: AddressSanitizer (ASan) is excellent here.
# It will explicitly report "ERROR: AddressSanitizer: stack-overflow"
# instead of just throwing a silent "Segmentation fault".
target_compile_options(day7 PRIVATE
        -Wall -Wextra -Wpedantic
        -fsanitize=address,undefined
)
target_link_options(day7 PRIVATE
        -fsanitize=address,undefined
)