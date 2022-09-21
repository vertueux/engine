cmake_minimum_required(VERSION 3.9)
project(opticus_camera VERSION 0.0.1 LANGUAGES CXX)

# [TO ADAPT] To make DLL export work, you have to put the .dll file next
# to the executable or other dynamic linked library files.
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../bin)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# C++ standard can be overridden when this is used as a sub-project.
if(NOT CMAKE_CXX_STANDARD)
  # This project is using C++20
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif(NOT CMAKE_CXX_STANDARD)

include_directories(${PROJECT_SOURCE_DIR/})

IF (CMAKE_SYSTEM_NAME MATCHES "windows")
  add_definitions(-DBASE_EXPORTS)
ENDIF()

add_library(${PROJECT_NAME} SHARED
  "public/camera/camera.cc"
  "public/camera/camera.h"
)

set_target_properties(opticus_camera PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:/public>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/public>
  PRIVATE
    $<INSTALL_INTERFACE:/>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/
    opticus_core 
    # "${GLM_BINARY_DIR}/glm" TO DO
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE 
    opticus_core 
)