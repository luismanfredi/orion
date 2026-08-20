cmake_minimum_required(VERSION 3.28)

project(orion VERSION 0.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -------------
# Main Library
# -------------

# Create Orion Library, main target
add_library(orion
    src/matrix.cpp
)

add_library(orion::orion ALIAS orion)

target_include_directories(orion
    PUBLIC
        # Generators Expressions
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> # When compiling local, use include that is in the root directory
        $<INSTALL_INTERFACE:include> # Search headers in include
)

target_compile_options(orion
    PRIVATE 
        -Wall  
        -Wextra 
        -Wpedantic
)

# ---------
# Examples
# ---------

# Create an .exe 
add_executable(orion_example
    examples/basic.cpp
)

# Connects the .exe with the library
target_link_libraries(orion_example
    PRIVATE
        orion::orion
)

# ------------------------------------
# Tests configuration (Catch2 + CTest)
# ------------------------------------

include(CTest)
enable_testing()

# Native CMake module to download external dependencies
include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.8.1
)

# Download Catch2 if not exists
FetchContent_MakeAvailable(Catch2)

# Compile tests in a different .exe, add Catch2::Catch2WithMain
add_executable(orion_tests
    tests/test_matrix.cpp 
)

# Connect to Orion library e brings native main() from Catch2
target_link_libraries(orion_tests
    PRIVATE
        orion::orion
        Catch2::Catch2WithMain
)

target_compile_options(orion_tests
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

# Integrate Catch2 tests into the CTest runner
include(Catch)
catch_discover_tests(orion_tests)

# ------------------------------------
# .clang-tidy configuration
# ------------------------------------

find_program(CLANG_TIDY clang-tidy)

if(CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})
endif()
