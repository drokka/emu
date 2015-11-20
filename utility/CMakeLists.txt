set(SOURCE_FILES  Parameter.h IterativeFunctionBase.h IterativeFunction.h index_sequence.h)

add_library(function_utilities SHARED ${SOURCE_FILES})

set_target_properties(function_utilities PROPERTIES LINKER_LANGUAGE CXX)

include_directories(/usr/include/cppunit)

link_directories(/usr/lib/x86_64-linux-gnu)
target_link_libraries(function_utilities libcppunit.so)
