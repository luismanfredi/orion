cmake_minimum_required(VERSION 3.28)

project(orion VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(orion
    src/main.cpp
)

target_compile_options(orion PRIVATE 
    -Wall  
    -Wextra 
    -Wpedantic)