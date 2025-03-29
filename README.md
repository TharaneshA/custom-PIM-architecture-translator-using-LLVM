# Matrix Multiplication Compiler for PIM Architecture

This project implements a compiler that translates C++ matrix multiplication programs into custom ISA instructions for a Processing-in-Memory (PIM) architecture.

## Project Structure

```
├── src/                    # Source code directory
│   ├── frontend/           # C++ parsing and AST generation
│   ├── middle/             # Optimization and IR generation
│   ├── backend/            # Custom ISA instruction generation
│   └── examples/           # Example matrix multiplication programs
├── include/                # Header files
├── lib/                    # Libraries
├── tests/                  # Test cases
└── docs/                   # Documentation
```

## Implementation Plan

1. Frontend Development
   - Parse C++ matrix multiplication code
   - Generate Abstract Syntax Tree (AST)
   - Validate matrix operations

2. Middle-end Processing
   - Convert AST to LLVM IR
   - Apply optimizations
   - Handle memory mapping

3. Backend Generation
   - Convert LLVM IR to custom ISA instructions
   - Implement physical memory mapping
   - Generate instruction stream

## Building and Running

Detailed instructions for building and running the compiler will be added as development progresses.

## Documentation

- Algorithm and Design documentation
- Implementation details
- Output format and examples

## References

- Research Paper: "Flexible Instruction Set Architecture for Programmable Look-up Table based Processing-in-Memory"
- LLVM Framework: https://llvm.org/