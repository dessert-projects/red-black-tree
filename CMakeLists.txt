cmake_minimum_required(VERSION 3.10)
project(red-black-tree)

if (True)
    set(gtest_force_shared_crt on cache bool "" force)
endif()
add_subdirectory(googletest)

# test
add_executable(test test.cpp red-black-tree.cpp red-black-tree.h)
target_link_libraries(test gtest)
