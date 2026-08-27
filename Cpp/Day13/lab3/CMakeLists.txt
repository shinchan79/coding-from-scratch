cmake_minimum_required(VERSION 3.10)
project(Day13_MemoryFragmentation)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day13_frag main.cpp)

# Note: DO NOT use AddressSanitizer (-fsanitize=address) for this specific benchmark.
# ASan overrides the system's default memory allocator with its own strict tracking
# mechanism, which will completely skew the fragmentation performance results.
target_compile_options(day13_frag PRIVATE
        -Wall -Wextra -Wpedantic
        -O2
)