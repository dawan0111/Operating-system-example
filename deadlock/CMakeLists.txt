cmake_minimum_required(VERSION 3.11)

set(PACKAGE_NAME DEADLOCK_EXAMPLE)
set(PACKAGE_VERSION 1.1.0)

project(${PACKAGE_NAME} VERSION ${PACKAGE_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(multithread_deadlock_example multithread_deadlock.cpp)
add_executable(deadlock_avoidance_example deadlock_avoidance.cpp)