cmake_minimum_required(VERSION 3.9)
project(engine VERSION 0.0.1 LANGUAGES CXX)

# C++ standard can be overridden when this is used as a sub-project.
if(NOT CMAKE_CXX_STANDARD)
  # This project is using C++20
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif(NOT CMAKE_CXX_STANDARD)

# Set the platform to Windows.
if (WIN32)
  set(OPTICUS_PLATFORM_NAME OPTICUS_PLATFORM_WINDOWS)
  add_definitions(-D_UNICODE -DUNICODE)
else (WIN32) 
  # Or Unix based operating systems.
  set(OPTICUS_PLATFORM_NAME OPTICUS_PLATFORM_POSIX)
endif (WIN32)
