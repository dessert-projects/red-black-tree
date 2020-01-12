cmake_minimum_required(VERSION 3.14)
project(red-black-tree)

if (MSVC) 
    set(gtest_force_shared_crt on cache bool "" force)
endif()
add_subdirectory(googletest)

add_executable(demo demo.cpp red-black-tree.cpp red-black-tree.h)

# test
add_executable(test test.cpp red-black-tree.cpp red-black-tree.h)
target_link_libraries(test gtest)
