#include "ir_parser.h"
#include <fstream>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Analysis/LoopInfo.h>
#include <llvm/Analysis/ScalarEvolution.h>
#include <llvm/Analysis/DependenceAnalysis.h>

ParsedCode parseLLVMIR(const std::string &filename) {
    ParsedCode result;
    llvm::LLVMContext context;
    llvm::SMDiagnostic err;
    
    // Parse LLVM IR file
    std::unique_ptr<llvm::Module> module = llvm::parseIRFile(filename, err, context);
    if (!module) {
        err.print("IR Parser", llvm::errs());
        return result;
    }
    
    // Analyze loops and memory accesses
    for (auto &func : *module) {
        if (func.isDeclaration()) continue;
        
        llvm::LoopInfo LI;
        llvm::ScalarEvolution SE(func);
        llvm::DependenceInfo DI(func, &SE);
        
        // Process loops
        for (auto *loop : LI) {
            LoopInfo loopInfo;
            loopInfo.loopDepth = loop->getLoopDepth();
            
            // Analyze memory accesses
            for (auto *block : loop->blocks()) {
                for (auto &inst : *block) {
                    if (inst.mayReadOrWriteMemory()) {
                        MemoryAccess access;
                        access.instruction = &inst;
                        loopInfo.memoryAccesses.push_back(access);
                    }
                }
            }
            
            result.loops.push_back(loopInfo);
        }
    }
    
    return result;
}