cmake_minimum_required(VERSION 3.10)
project(Lab3_Fmt)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(fmt CONFIG REQUIRED)

add_executable(app_fmt main.cpp)

target_link_libraries(app_fmt PRIVATE fmt::fmt)