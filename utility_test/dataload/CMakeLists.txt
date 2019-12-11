set(SOURCE_FILES testdataload.cpp ../../../symicon/PaintIcon.cpp ../../../symicon/PaintIcon.h)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(testdataload ${SOURCE_FILES})

include_directories(/usr/include/cairo)
include_directories(../function_utilities/utility)

link_directories(/usr/lib/x86_64-linux-gnu)
target_link_libraries(testdataload libcairo.so.2 emutil)