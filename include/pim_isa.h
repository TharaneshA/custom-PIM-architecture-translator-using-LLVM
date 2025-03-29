#ifndef PIM_ISA_H
#define PIM_ISA_H

// PIM Instruction Set Architecture Definitions

// Basic Instruction Types
#define PIM_MOV  0x01  // Move data between registers/memory
#define PIM_ADD  0x02  // Addition
#define PIM_MUL  0x03  // Multiplication
#define PIM_LOAD 0x04  // Load from memory
#define PIM_STORE 0x05 // Store to memory
#define PIM_ACCUM 0x06 // Accumulate operation
#define PIM_BRANCH 0x07 // Conditional branch
#define PIM_JUMP 0x08  // Unconditional jump

// Parallel Execution Markers
#define PAR_BEGIN 0x10 // Begin parallel execution
#define PAR_END   0x11 // End parallel execution

// Processing Element Masks
#define PE_ALL 0xFF    // All processing elements
#define PE_ANY 0x00    // Any processing element

#endif // PIM_ISA_H