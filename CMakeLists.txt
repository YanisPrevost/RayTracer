cmake_minimum_required(VERSION 3.16)
project(RayTracer)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Plugins/Primitives)

set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/..)

add_subdirectory(src)
