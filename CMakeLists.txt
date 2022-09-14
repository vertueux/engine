cmake_minimum_required(VERSION 3.9)
project(opticus_master VERSION 0.0.1 LANGUAGES CXX)

# C++ standard can be overridden when this is used as a sub-project.
if(NOT CMAKE_CXX_STANDARD)
  # This project is using C++20
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif(NOT CMAKE_CXX_STANDARD)

# Direct link to Opticus.
add_subdirectory(opticus)

# Direct link to samples.
add_subdirectory(samples)