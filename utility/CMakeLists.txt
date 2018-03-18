set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


add_library(emutil SHARED FrequencyData.cpp FrequencyData.h Generator.cpp Generator.h index_sequence.h
        IntegerPoint.h IntegerPoint2D.h IntegerPoint2D.cpp IterativeFunction.h
        IterativeFunctionBase.h  Parameter.h Point.h Point2D.h PointList.h PointList.cpp )