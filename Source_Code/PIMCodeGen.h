#ifndef PIM_CODE_GEN_H
#define PIM_CODE_GEN_H

#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <string>
#include <vector>

namespace pim_compiler {

class PIMCodeGenerator {
public:
    PIMCodeGenerator() = default;

    // Main code generation methods
    bool generatePIMInstructions(llvm::Module &M);
    void optimizeMemoryAccess(llvm::Function &F);
    void generateInstructionStream(const std::string &outputFile);

private:
    struct PIMInstruction {
        std::string opcode;
        std::vector<std::string> operands;
        unsigned memoryAddress;
    };

    std::vector<PIMInstruction> instructions;

    // Helper methods
    void handleMatrixMultiplication(llvm::Function &F);
    void allocateRegisters(llvm::Function &F);
    void scheduleInstructions();
    void optimizeInstructionStream();
};

} // namespace pim_compiler

#endif // PIM_CODE_GEN_H