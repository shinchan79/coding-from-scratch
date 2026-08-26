cmake_minimum_required(VERSION 3.10)
project(Lab2_MemoryCheck)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app_asan main.cpp)
add_executable(app_valgrind main.cpp)

target_compile_options(app_asan PRIVATE -fsanitize=address)
target_link_options(app_asan PRIVATE -fsanitize=address)