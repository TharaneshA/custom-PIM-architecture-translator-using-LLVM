#include "PIMCodeGen.h"
#include <fstream>
#include <sstream>
#include <cassert>

namespace pim_compiler {

bool PIMCodeGenerator::generatePIMInstructions(llvm::Module &M) {
    for (auto &F : M) {
        if (F.getName() == "matrix_multiply") {
            handleMatrixMultiplication(F);
        }
    }
    optimizeInstructionStream();
    return true;
}

void PIMCodeGenerator::handleMatrixMultiplication(llvm::Function &F) {
    // Analyze matrix dimensions and memory layout
    for (auto &BB : F) {
        for (auto &I : BB) {
            if (auto *load = llvm::dyn_cast<llvm::LoadInst>(&I)) {
                // Generate load instructions for matrix elements
                PIMInstruction loadInst;
                loadInst.opcode = "LOAD";
                loadInst.memoryAddress = calculateMemoryAddress(load);
                instructions.push_back(loadInst);
            }
            else if (auto *mul = llvm::dyn_cast<llvm::MulOperator>(&I)) {
                // Generate multiply-accumulate instructions
                PIMInstruction macInst;
                macInst.opcode = "MAC";
                macInst.operands = getOperandRegisters(mul);
                instructions.push_back(macInst);
            }
        }
    }
}

void PIMCodeGenerator::optimizeMemoryAccess(llvm::Function &F) {
    // Implement memory access pattern optimization
    // Map matrix elements to physical memory locations
    for (auto &inst : instructions) {
        if (inst.opcode == "LOAD" || inst.opcode == "STORE") {
            inst.memoryAddress = optimizeMemoryMapping(inst.memoryAddress);
        }
    }
}

void PIMCodeGenerator::generateInstructionStream(const std::string &outputFile) {
    std::ofstream out(outputFile);
    for (const auto &inst : instructions) {
        // Format according to custom ISA specification
        std::stringstream ss;
        ss << inst.opcode << " ";
        for (const auto &op : inst.operands) {
            ss << op << " ";
        }
        if (inst.memoryAddress != 0) {
            ss << "@" << inst.memoryAddress;
        }
        out << ss.str() << "\n";
    }
    out.close();
}

void PIMCodeGenerator::optimizeInstructionStream() {
    // Implement instruction-level optimizations
    // Reorder instructions for better parallelism
    // Eliminate redundant memory accesses
    for (size_t i = 0; i < instructions.size(); ++i) {
        if (i + 1 < instructions.size()) {
            if (canCombineInstructions(instructions[i], instructions[i + 1])) {
                mergeInstructions(instructions[i], instructions[i + 1]);
                instructions.erase(instructions.begin() + i + 1);
                --i;
            }
        }
    }
}

unsigned PIMCodeGenerator::calculateMemoryAddress(llvm::LoadInst* load) {
    // Calculate physical memory address based on array indices
    if (auto *GEP = llvm::dyn_cast<llvm::GetElementPtrInst>(load->getPointerOperand())) {
        unsigned baseAddr = 0;
        if (GEP->getNumIndices() == 2) {
            auto *rowIdx = llvm::dyn_cast<llvm::ConstantInt>(GEP->getOperand(1));
            auto *colIdx = llvm::dyn_cast<llvm::ConstantInt>(GEP->getOperand(2));
            if (rowIdx && colIdx) {
                baseAddr = rowIdx->getZExtValue() * 1024 + colIdx->getZExtValue();
            }
        }
        return baseAddr;
    }
    return 0;
}

std::vector<std::string> PIMCodeGenerator::getOperandRegisters(llvm::Value* val) {
    std::vector<std::string> regs;
    if (auto *op = llvm::dyn_cast<llvm::Instruction>(val)) {
        for (unsigned i = 0; i < op->getNumOperands(); ++i) {
            regs.push_back("R" + std::to_string(i));
        }
    }
    return regs;
}

unsigned PIMCodeGenerator::optimizeMemoryMapping(unsigned addr) {
    // Implement memory mapping optimization
    // This is a simple example - actual implementation would depend on PIM architecture
    return (addr % 1024) * 4; // Align to 4-byte boundaries
}

bool PIMCodeGenerator::canCombineInstructions(const PIMInstruction& inst1, const PIMInstruction& inst2) {
    // Check if two instructions can be combined for better efficiency
    return inst1.opcode == "LOAD" && inst2.opcode == "MAC" &&
           inst1.memoryAddress + 4 == inst2.memoryAddress;
}

void PIMCodeGenerator::mergeInstructions(PIMInstruction& inst1, const PIMInstruction& inst2) {
    // Merge two compatible instructions
    inst1.opcode = "LOAD_MAC";
    inst1.operands.insert(inst1.operands.end(), 
                         inst2.operands.begin(), 
                         inst2.operands.end());
}

} // namespace pim_compiler