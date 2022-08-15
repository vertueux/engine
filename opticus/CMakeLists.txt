cmake_minimum_required(VERSION 3.9)
project(opticus VERSION 0.0.1 LANGUAGES CXX)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)

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

include_directories(${PROJECT_SOURCE_DIR/})

IF (CMAKE_SYSTEM_NAME MATCHES "windows")
add_definitions(-DBASE_EXPORTS)
ENDIF()


#################################################################### 
#                                                                  #
#                Choose the ones you want to delete                #
#                                                                  #
#################################################################### 

# Direct link to the engine core (Removing it will prevent the engine from working)
add_subdirectory(core)

# Direct link to the engine runtime.
add_subdirectory(runtime)

# Only if the user's platform is Microsoft Windows.
IF (WIN32)
  add_subdirectory(windows)
ENDIF()

####################################################################

