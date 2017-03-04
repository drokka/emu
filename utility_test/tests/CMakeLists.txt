include_directories(../gtest/gtest-1.7.0/include ../gtest/gtest-1.7.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(testsrun main.cpp ParameterTest.h IterativeFunctionTest.h Point2DTest.h PointListTest.h ../../utility/FrequencyData.h)

target_link_libraries(testsrun gtest gtest_main)