cmake_minimum_required(VERSION 3.7)
project(Lab3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp main.h Hash.cpp Hash.h Random.h Random.cpp xxhash.c xxhash.h)
add_executable(Lab3 ${SOURCE_FILES})

target_link_libraries(Lab3 pthread)