cmake_minimum_required(VERSION 3.20)

project(OcctTest)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(DEBUG "Enable Debug" ON)
configure_file(OcctTestConfig.h.in ${PROJECT_BINARY_DIR}/OcctTestConfig.h @ONLY)

include_directories(OcctTest PUBLIC
  "${PROJECT_BINARY_DIR}"
  /usr/include/opencascade/
  /usr/include/python3.9
  )

add_executable(OcctTest main.cpp)
add_library(PyOCCT pyocct.cpp)
