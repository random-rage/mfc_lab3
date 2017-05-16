cmake_minimum_required(VERSION 3.7)
project(Lab3)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_RELEASE "-O1")
set(SOURCE_FILES main.cpp main.h Hash.cpp Hash.h Random.h Random.cpp xxhash.c xxhash.h)

add_executable(Lab3 ${SOURCE_FILES})
    target_compile_definitions(Lab3 PRIVATE HASH_32)
    target_link_libraries(Lab3 pthread)

add_executable(Lab3_64 ${SOURCE_FILES})
    target_compile_definitions(Lab3_64 PRIVATE HASH_64)
    target_link_libraries(Lab3_64 pthread)