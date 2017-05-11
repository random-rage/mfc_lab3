cmake_minimum_required(VERSION 3.7)
project(Lab3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Hash.cpp Hash.h)
add_executable(Lab3 ${SOURCE_FILES})

target_link_libraries(Lab3 pthread)