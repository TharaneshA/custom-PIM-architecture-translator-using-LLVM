#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include "MatrixAnalysisPass.h"
#include "PIMCodeGen.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input-file>" << std::endl;
        return 1;
    }

    // Initialize LLVM context and module
    llvm::LLVMContext context;
    std::unique_ptr<llvm::Module> module = std::make_unique<llvm::Module>("matrix_mul", context);
    
    // Parse input file and generate LLVM IR
    if (!generateLLVMIR(argv[1], module.get())) {
        std::cerr << "Failed to generate LLVM IR" << std::endl;
        return 1;
    }

    // Run matrix analysis pass
    MatrixAnalysisPass pass;
    if (!pass.runOnModule(*module)) {
        std::cerr << "Matrix analysis failed" << std::endl;
        return 1;
    }

    // Generate PIM ISA code
    PIMCodeGen codegen(pass.getMatrixOps());
    if (!codegen.generateISA("isa_output.txt")) {
        std::cerr << "Failed to generate ISA code" << std::endl;
        return 1;
    }

    std::cout << "Successfully generated PIM ISA code" << std::endl;
    return 0;
}