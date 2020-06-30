cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

project(ModulerMadness)

set(CMAKE_BUILD_TYPE Debug)
 
include_directories(include)
 
file(GLOB SOURCES "src/*.cpp")
 
add_executable(main ${SOURCES})