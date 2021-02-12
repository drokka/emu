set(SOURCE_FILES testdataload.cpp )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(testdataload ${SOURCE_FILES})

include_directories(../../utility)

link_directories(../../)
target_link_libraries(testdataload  emutil)