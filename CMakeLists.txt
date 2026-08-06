cmake_minimum_required(VERSION 3.28)

project(orion VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(orion_example
    examples/basic.cpp
    src/matrix.cpp
)

target_include_directories(orion_example PRIVATE include)

target_compile_options(orion_example PRIVATE 
    -Wall  
    -Wextra 
    -Wpedantic)