cmake_minimum_required(VERSION 3.3)
project(function_utilities)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(/usr/include/cppunit ./ /usr/include ../../stb)


add_library(emutil SHARED FrequencyData.cpp FrequencyData.h Generator.cpp Generator.h index_sequence.h
        IntegerPoint.h IntegerPoint2D.h IntegerPoint2D.cpp IterativeFunction.h
        IterativeFunctionBase.h  Parameter.h Point.h Point2D.h PointList.h PointList.cpp ColourIcon.h ColourIcon.cpp
        QuiltIcon.h QuiltIcon.cpp SymIconApp.cpp SymIconApp.h
      # runsample.cpp
        runsampleNoJni.cpp
        image/PaintIcon.cpp image/PaintIcon.h)

set_property(TARGET emutil PROPERTY INTERFACE_POSITION_INDEPENDENT_CODE ON)
#set_property(TARGET emutil PROPERTY ENABLE_XOM false)
add_executable(symirun  main.cpp)

target_link_libraries(symirun emutil m)

