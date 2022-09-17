include_directories(../gtest/gtest-1.7.0/include ../gtest/gtest-1.7.0 ../../utility)

add_executable(testsrun main.cpp ParameterTest.h IterativeFunctionTest.h Point2DTest.h PointListTest.h )

target_link_libraries(testsrun gtest gtest_main emutil)

