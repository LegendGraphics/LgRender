# CMake version requirement
cmake_minimum_required(VERSION 2.8)

project( LgRender )

FILE( GLOB Project_SRCS "core/*.*" )		
SET( Project_INCLUDE_DIR core/)

INCLUDE_DIRECTORIES( ${Project_INCLUDE_DIR} 
                     ${CMAKE_CURRENT_BINARY_DIR} )

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_executable(LgRender ${Project_SRCS})