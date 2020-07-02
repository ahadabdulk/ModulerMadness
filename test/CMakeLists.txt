
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories(
  ${SOURCE_DIR}
  ${INCLUDE_DIR}
  ${GTEST_INCLUDE_DIR}
)

add_executable(test${PROJECT_NAME}
  main.cpp
  testSuit.cpp
)

target_link_libraries(test${PROJECT_NAME}
  lib${PROJECT_NAME}
  ${GTEST_LIB_DIR}/libgtest.a
  pthread
)

install(TARGETS test${PROJECT_NAME} DESTINATION ${INSTALL_BIN_DIR})