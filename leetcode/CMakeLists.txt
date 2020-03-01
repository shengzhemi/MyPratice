cmake_minimum_required(VERSION 3.10)

set(SRC_LISTS NO-8.cpp)

add_subdirectory(gtest)

add_executable(runtest ${SRC_LISTS})
target_link_libraries(runtest gtest_main)
