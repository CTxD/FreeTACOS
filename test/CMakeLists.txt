cmake_minimum_required(VERSION 3.5)

project(freetacos LANGUAGES CXX VERSION 0.0.1)

find_package(Catch2 REQUIRED)
add_executable(foo_test test.cpp)
target_link_libraries(foo_test Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(foo_test)
