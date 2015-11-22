include_directories(../gtest/gtest-1.7.0/include ../gtest/gtest-1.7.0)

add_executable(testsrun main.cpp ParameterTest.h IterativeFunctionTest.h Point2DTest.h)

target_link_libraries(testsrun gtest gtest_main)
target_link_libraries(testsrun function_utilities)