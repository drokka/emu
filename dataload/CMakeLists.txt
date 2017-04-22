set(SOURCE_FILES  dataload.cpp )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(dataload ${SOURCE_FILES})

include_directories(/usr/include/cairo)
include_directories(../function_utilities/utility)

link_directories(/usr/lib/x86_64-linux-gnu)
target_link_libraries(dataload libcairo.so.2 emutil)