cmake_minimum_required(VERSION 3.11)

set(PACKAGE_NAME POSIX_SHARED_MEMORY_EXAMPLE)
set(PACKAGE_VERSION 1.1.0)

project(${PACKAGE_NAME} VERSION ${PACKAGE_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(shm_provider shm_provider.cpp)
add_executable(shm_customer shm_customer.cpp)