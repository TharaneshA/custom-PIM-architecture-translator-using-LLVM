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
./pim_translator input.ll output.isa
```

## Dependencies
- LLVM
- CMake

## License
MIT