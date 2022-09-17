cmake_minimum_required(VERSION 3.3)
project(function_utilities)

#set(SOURCE_FILES utility_test/tests/main.cpp)


include_directories(../utility)
include_directories(/usr/include/cppunit)

add_subdirectory(gtest)

add_subdirectory(tests)
add_subdirectory(dataload)
