cmake_minimum_required(VERSION 3.0)

project(cppGPIO)
set (CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES *.cpp include/*.h)

# Include header files
include_directories ("${PROJECT_SOURCE_DIR}/include")

add_executable(${PROJECT_NAME} ${SOURCES})
