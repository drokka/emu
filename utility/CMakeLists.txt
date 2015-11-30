set(SOURCE_FILES  Parameter.h IterativeFunctionBase.h IterativeFunction.h index_sequence.h
        IntegerPoint.h IntegerPoint2D.h Point.h Point2D.h PointList.h
        )

add_library(function_utilities SHARED ${SOURCE_FILES})

set_target_properties(function_utilities PROPERTIES LINKER_LANGUAGE CXX)


link_directories(/usr/lib/x86_64-linux-gnu)
