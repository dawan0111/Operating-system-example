cmake_minimum_required(VERSION 3.11)

set(PACKAGE_NAME SYNCHRONIZATIION_EXAMPLE)
set(PACKAGE_VERSION 1.1.0)

project(${PACKAGE_NAME} VERSION ${PACKAGE_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(reader_writer_example reader_writer_example.cpp)
add_executable(atomic_variable_example atomic_variable_example.cpp)
add_executable(atomic_mutex_compare_example atomic_mutex_compare_example.cpp)