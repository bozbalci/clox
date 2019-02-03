cmake_minimum_required(VERSION 3.13)
project(clox C)

set(CMAKE_C_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(lib)
add_subdirectory(tool)
