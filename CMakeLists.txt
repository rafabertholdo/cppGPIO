cmake_minimum_required(VERSION 3.0)

project(cppGPIO)
set (CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES main.cpp)
file(GLOB LIB_SOURCES GPIO.cpp)

add_library(${PROJECT_NAME} ${LIB_SOURCES})

# Include header files
target_include_directories (${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_executable(example1 ${SOURCES})
target_link_libraries(example1 LINK_PUBLIC ${PROJECT_NAME})
