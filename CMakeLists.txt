cmake_minimum_required(VERSION 3.3)
project(function_utilities)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES utility_test/tests/main.cpp)


include_directories(utility)
include_directories(/usr/include/cppunit)

add_subdirectory(utility)

add_subdirectory(utility_test)
