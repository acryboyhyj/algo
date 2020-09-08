cmake_minimum_required(VERSION 2.8)

project(tree)
add_definitions(-std=c++11 -g -Wall)
include_directories(${PROJECT_SOURCE_DIR})
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR} SrcList)
#set(SrcList
#    BinarySearchTreeTest.cpp
#)

add_executable(tree ${SrcList})

target_link_libraries(tree
                        pthread)