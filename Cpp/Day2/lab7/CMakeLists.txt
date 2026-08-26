cmake_minimum_required(VERSION 3.10)
project(UndefinedBehaviorLab)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -g and -O0 to keep debug symbols and prevent the compiler from deleting the UB code.
# -Wno-uninitialized is used ONLY for this lab to force the compiler to ignore our intentional mistake.
add_compile_options(-g -O0 -Wall -Wextra -Wpedantic -Wno-uninitialized)

add_executable(app_ub main.cpp)

# Enable UBSan and force it to crash immediately upon detecting UB
target_compile_options(app_ub PRIVATE -fsanitize=undefined -fno-sanitize-recover=undefined)
target_link_options(app_ub PRIVATE -fsanitize=undefined -fno-sanitize-recover=undefined)