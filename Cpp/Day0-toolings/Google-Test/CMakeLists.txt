cmake_minimum_required(VERSION 3.10)
project(Lab4_StandaloneTest)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest CONFIG REQUIRED)

add_executable(app_test test.cpp)

target_link_libraries(app_test PRIVATE GTest::gtest GTest::gtest_main)

enable_testing()
add_test(NAME Test_Lab4 COMMAND app_test)