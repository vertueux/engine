cmake_minimum_required(VERSION 3.5)
project(tests VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)

add_executable(${PROJECT_NAME} main.cc)

link_directories(${PROJECT_SOURCE_DIR}/bin)
target_link_libraries(${PROJECT_NAME} opticus)
