cmake_minimum_required(VERSION 3.13.4)
project(matrix_compiler)

# Specify build tool
if(NOT CMAKE_MAKE_PROGRAM)
    find_program(CMAKE_MAKE_PROGRAM NAMES ninja ninja-build)
    if(NOT CMAKE_MAKE_PROGRAM)
        message(FATAL_ERROR "Ninja build tool not found. Please install Ninja.")
    endif()
endif()

# Find LLVM package
find_package(LLVM REQUIRED CONFIG)

# Add LLVM definitions and include directories
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add source files
set(SOURCES
    Source_Code/main.cpp
    src/frontend/parser.cpp
    src/middle/llvm_generator.cpp
    src/backend/isa_generator.cpp
    src/examples/matrix_mul.cpp
)

# Create executable
add_executable(matrix_compiler ${SOURCES})

# Link against LLVM libraries
target_link_libraries(matrix_compiler PRIVATE LLVM)

# Set output directories
set_target_properties(matrix_compiler PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)