# PIM Architecture Translator using LLVM

A compiler that translates LLVM IR to custom PIM (Processing-In-Memory) architecture instructions.

## Features
- Parses LLVM IR code
- Analyzes loops for parallelization opportunities
- Maps memory accesses to PIM architecture
- Generates PIM ISA instructions

## Build Instructions
```bash
mkdir build
cd build
cmake ..
make
```

## Usage
```bash
# Generate LLVM IR from the matrix multiplication example
clang++ -S -emit-llvm ../examples/matrix_mult.cpp -o matrix_mult.ll

# Run the matrix multiplication example directly
./examples/matrix_mult

# Run the PIM compiler on the LLVM IR
./pim_compiler matrix_mult.ll matrix_mult.isa

# View the three-address code (displayed in terminal)

# View the generated ISA instructions
cat matrix_mult.isa

# Convert ISA to ISA 24bit format from Research Paper
./examples/isa_converter matrix_mult.isa matrix_mult_paper.isa
```
## Dependencies
- LLVM
- CMake

## License
MIT