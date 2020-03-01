cmake_minimum_required(VERSION 3.10)

#add current source file to SRC_LIST
aux_source_directory(. SRC_LISTS)
add_subdirectory(gtest)

add_executable(runtest ${SRC_LISTS})
target_link_libraries(runtest gtest_main)
