set(SOURCE_FILES  ../utility/Parameter.h ../utility/IterativeFunctionBase.h ../utility/IterativeFunction.h ../utility/index_sequence.h
        ../utility/IntegerPoint.h ../utility/IntegerPoint2D.h ../utility/Point.h ../utility/Point2D.h ../utility/PointList.h
        ../utility/Generator.h dataload.cpp ../utility/FrequencyData.h)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(dataload ${SOURCE_FILES})

include_directories(/usr/include/cairo)
include_directories(../function_utilities/utility)

link_directories(/usr/lib/x86_64-linux-gnu)
target_link_libraries(dataload libcairo.so.2)