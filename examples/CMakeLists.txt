cmake_minimum_required(VERSION 3.10)

# Add the matrix multiplication example
add_executable(matrix_mult matrix_mult.cpp)

# Set C++ standard
set_target_properties(matrix_mult PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)