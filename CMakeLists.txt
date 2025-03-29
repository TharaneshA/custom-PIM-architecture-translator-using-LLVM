cmake_minimum_required(VERSION 3.10)
project(pim_translator)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find LLVM package
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Set LLVM include paths
list(APPEND CMAKE_MODULE_PATH "${LLVM_DIR}")
include_directories(
    ${LLVM_INCLUDE_DIRS}
    ${LLVM_MAIN_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Add LLVM specific definitions and includes
include_directories(
    ${LLVM_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_definitions(${LLVM_DEFINITIONS})

# Link against required LLVM components
llvm_map_components_to_libnames(llvm_libs
    support
    core
    irreader
    bitreader
    bitwriter
    analysis
    transformsutils
    passes
)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(examples)