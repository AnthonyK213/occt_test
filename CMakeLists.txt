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

include_directories(OcctTest PUBLIC
  "${PROJECT_BINARY_DIR}"
  $ENV{CONDA_PREFIX}/include/python3.9
  )

include_directories(${OpenCASCADE_INCLUDE_DIR})
#MESSAGE("OCC-Include-Dir: ${OpenCASCADE_INCLUDE_DIR}")
link_directories(${OpenCASCADE_LIBRARY_DIR})
#MESSAGE("OCC-Lib-Dir: ${OpenCASCADE_LIBRARY_DIR}")
#MESSAGE("OCC-Libs: ${OpenCASCADE_LIBRARIES}")

SET(OpenCASCADE_LIBS 
  TKernel
  TKService
  TKV3d
  TKOpenGl
  TKBRep
  TKGeomBase
  TKGeomAlgo
  TKG3d
  TKG2d
  TKTopAlgo
  TKPrim
)

#if(UNIX AND NOT APPLE)
  #find_library(FreeType REQUIRED)

  #find_path (FONTCONFIG_INCLUDE_DIRS "fontconfig/fontconfig.h")
  #find_library(FontConfig REQUIRED)
#endif()

#target_link_libraries(OcctTest PRIVATE OpenCASCADE)

#add_library(PyOCCT SHARED pyocct.cpp)

add_executable(OcctTest main.cpp)

target_link_libraries(
  OcctTest
  ${OpenCASCADE_LIBS}
)
