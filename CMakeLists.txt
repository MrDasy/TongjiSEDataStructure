cmake_minimum_required(VERSION 3.20)
project(SSEDataStructure)

set(CMAKE_CXX_STANDARD 14)

#add_executable(SSEDataStructure DataStructures.hpp T10.cpp Algorithms.hpp)
file(GLOB_RECURSE mains RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/T*.cpp")
foreach(mainfile IN LISTS mains)
    # Get file name without directory
    get_filename_component(mainname ${mainfile} NAME_WE)
    add_executable(${mainname} ${mainfile})
endforeach()