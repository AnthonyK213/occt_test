cmake_minimum_required(VERSION 3.20)

project(OcctTest)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(CMAKE_CXX_EXTENSIONS OFF)

option(DEBUG "Enable Debug" ON)
configure_file(OcctTestConfig.h.in ${PROJECT_BINARY_DIR}/OcctTestConfig.h @ONLY)

find_package(OpenCASCADE COMPONENTS FoundationClasses REQUIRED)
find_package(OpenCASCADE COMPONENTS ModelingAlgorithms REQUIRED)
find_package(OpenCASCADE COMPONENTS ModelingData REQUIRED)
find_package(OpenCASCADE COMPONENTS DataExchange REQUIRED)
find_package(OpenCASCADE COMPONENTS Visualization REQUIRED)

find_package(pybind11 REQUIRED)
find_package(Python3 COMPONENTS Interpreter Development)

include_directories(OcctTest PUBLIC "${PROJECT_BINARY_DIR}")

include_directories(OcctTest PRIVATE "${Python3_INCLUDE_DIRS}")
MESSAGE("Python3-Include-Dirs: ${Python3_INCLUDE_DIRS}")
link_directories(${Python3_LIBRARY_DIRS})
MESSAGE("Python3-Library-Dirs: ${Python3_LIBRARY_DIRS}")

include_directories(${OpenCASCADE_INCLUDE_DIR})
MESSAGE("OCC-Include-Dir: ${OpenCASCADE_INCLUDE_DIR}")
link_directories(${OpenCASCADE_LIBRARY_DIR})
MESSAGE("OCC-Lib-Dir: ${OpenCASCADE_LIBRARY_DIR}")
MESSAGE("OCC-Libs: ${OpenCASCADE_LIBRARIES}")

pybind11_add_module(pyRpOCCT pyocct.cpp)

add_executable(OcctTest main.cpp)

target_link_libraries(
  OcctTest
  PRIVATE
  ${OpenCASCADE_LIBRARIES}
  python3.9
  )

target_link_libraries(
  pyRpOCCT
  PRIVATE
  ${OpenCASCADE_LIBRARIES}
  )
