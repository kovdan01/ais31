cmake_minimum_required(VERSION 3.5)

project(ais31 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS tests.h block.h)
set(SOURCES main.cpp tests.cpp)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
