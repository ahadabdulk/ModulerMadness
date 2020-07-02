
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories(include)

file(GLOB SOURCES "*.cpp")

add_library(lib${PROJECT_NAME} ${SOURCES})
install(TARGETS lib${PROJECT_NAME} DESTINATION ${INSTALL_LIB_DIR})

add_executable(${PROJECT_NAME} ${SOURCES})
install(TARGETS ${PROJECT_NAME} DESTINATION ${INSTALL_BIN_DIR})
