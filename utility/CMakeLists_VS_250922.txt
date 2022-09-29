cmake_minimum_required(VERSION 3.3)
set(CMAKE_CXX_STANDARD 14)

project(function_utilities)
#This is the NO JINI (C/C++ connect) version.
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#include_directories(/usr/include/cppunit ./ /usr/include ../../stb)
include_directories( ./ )    #VS
add_library(emutil STATIC
#add_library(emutil SHARED
        FrequencyData.cpp FrequencyData.h Generator.cpp Generator.h index_sequence.h
        IntegerPoint.h IntegerPoint2D.h IntegerPoint2D.cpp IterativeFunction.h
        IterativeFunctionBase.h  Parameter.h Point.h Point2D.h PointList.h PointList.cpp ColourIcon.h ColourIcon.cpp
        QuiltIcon.h QuiltIcon.cpp SymIconApp.cpp SymIconApp.h
     #  runsample.cpp
        runsampleNoJni.cpp
        #runsamplenj.h runsamplenj.cpp
        )

set_property(TARGET emutil PROPERTY INTERFACE_POSITION_INDEPENDENT_CODE ON)
#set_property(TARGET emutil PROPERTY ENABLE_XOM false)
add_executable(symirun  main.cpp)

#target_link_libraries(symirun emutil m)


#find_library(boost libboost D:/tools/boost_1_80_0/boost_1_80_0/stage/lib)
link_directories(D:/tools/boost_1_80_0/boost_1_80_0/stage/lib)
include_directories(D:/tools/boost_1_80_0/boost_1_80_0
        "C:/Program Files (x86)/libpng/include" "C:/Program Files/zlib/include")

add_library(boost STATIC IMPORTED)
set_target_properties(boost PROPERTIES
        IMPORTED_LOCATION D:/tools/boost_1_80_0/boost_1_80_0/stage/lib/libboost_filesystem-vc143-mt-gd-x64-1_80.lib
        INTERFACE_INCLUDE_DIRECTORIES D:/tools/boost_1_80_0/boost_1_80_0)

add_library(png STATIC IMPORTED) # or STATIC instead of SHARED
set_target_properties(png PROPERTIES
        IMPORTED_LOCATION "C:\\Program Files (x86)\\libpng\\lib\\libpng16_staticd.lib"
        INTERFACE_INCLUDE_DIRECTORIES "C:/Program Files (x86)/libpng/include"
        )

add_library(zlib STATIC IMPORTED) # or STATIC instead of SHARED
set_target_properties(zlib PROPERTIES
        IMPORTED_LOCATION "C:\\Program Files\\zlib\\lib\\zlibstatic.lib"
        INTERFACE_INCLUDE_DIRECTORIES "C:\\Program Files\\zlib\\include"
        )
add_executable(symiapp symiapp.cpp)
target_link_libraries(symiapp emutil png zlib boost)

target_link_libraries(symirun emutil)

#target_link_libraries(symiapp emutil m)
#target_sources(symiapp "symiapp.cpp")

#tests
#                add_subdirectory(utility_test)

install(TARGETS symiapp
        RUNTIME DESTINATION "D:\\working" )     #/mnt/d/working)

