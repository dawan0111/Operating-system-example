cmake_minimum_required(VERSION 3.11)

set(PACKAGE_NAME POSIX_PROCESS_EXAMPLE)
set(PACKAGE_VERSION 1.1.0)

project(${PACKAGE_NAME} VERSION ${PACKAGE_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(new_proc_pid new_proc_pid.cpp)
add_executable(pipe pipe.cpp)