cmake_minimum_required(VERSION 2.8)

project(graph)
add_definitions(-std=c++11 -g -Wall)
include_directories(${PROJECT_SOURCE_DIR})
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR} SrcList)


add_executable(graph ${SrcList})

target_link_libraries(graph
                        pthread)