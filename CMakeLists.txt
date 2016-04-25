# CMake version requirement
cmake_minimum_required(VERSION 2.8)

project( LgRender )

FILE( GLOB Project_SRCS "core/*.*" "shapes/*.*" "math/*.*")		
SET( Project_INCLUDE_DIR core/ shapes/ math/)

INCLUDE_DIRECTORIES( ${Project_INCLUDE_DIR} 
                     ${CMAKE_CURRENT_BINARY_DIR} )

add_executable(LgRender ${Project_SRCS})