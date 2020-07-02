cmake_minimum_required(VERSION 3.17)
project(ModulerMadness)

option(BUILD_TEST "Build Unit tests" OFF)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(INSTALL_BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dist/bin/${CMAKE_BUILD_TYPE}")
set(INSTALL_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dist/lib/${CMAKE_BUILD_TYPE}")
#set(INSTALL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dist/include")

add_subdirectory(external)
add_subdirectory(src)
#add_subdirectory(include)

if(BUILD_TEST)
  add_subdirectory(test)
endif()

