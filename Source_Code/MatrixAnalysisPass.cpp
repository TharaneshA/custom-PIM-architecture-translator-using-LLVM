#include "MatrixAnalysisPass.h"
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Constants.h>

namespace pim_compiler {

char MatrixAnalysisPass::ID = 0;

bool MatrixAnalysisPass::runOnModule(llvm::Module &M) {
    bool modified = false;
    
    for (auto &F : M) {
        if (F.getName() == "matrix_multiply") {
            modified |= detectMatrixOperations(F);
            analyzeAccessPatterns(F);
            identifyOptimizationOpportunities(F);
        }
    }
    
    return modified;
}

void MatrixAnalysisPass::getAnalysisUsage(llvm::AnalysisUsage &AU) const {
    AU.setPreservesAll();
}

bool MatrixAnalysisPass::detectMatrixOperations(llvm::Function &F) {
    bool found = false;
    
    // Collect matrix information from function parameters
    collectMatrixInfo(F);
    
    for (auto &BB : F) {
        for (auto &I : BB) {
            if (auto *load = llvm::dyn_cast<llvm::LoadInst>(&I)) {
                // Analyze matrix element loads
                if (auto *GEP = llvm::dyn_cast<llvm::GetElementPtrInst>(load->getPointerOperand())) {
                    found = true;
                }
            }
            else if (auto *store = llvm::dyn_cast<llvm::StoreInst>(&I)) {
                // Analyze matrix element stores
                if (auto *GEP = llvm::dyn_cast<llvm::GetElementPtrInst>(store->getPointerOperand())) {
                    found = true;
                }
            }
        }
    }
    
    return found;
}

void MatrixAnalysisPass::analyzeAccessPatterns(llvm::Function &F) {
    for (auto &BB : F) {
        for (auto &I : BB) {
            if (auto *GEP = llvm::dyn_cast<llvm::GetElementPtrInst>(&I)) {
                // Analyze matrix access patterns for optimization
                if (GEP->getNumIndices() == 2) {
                    // Handle 2D matrix access
                    auto *rowIdx = GEP->getOperand(1);
                    auto *colIdx = GEP->getOperand(2);
                    
                    // Record access pattern for optimization
                    if (auto *rowLoop = llvm::dyn_cast<llvm::PHINode>(rowIdx)) {
                        // Identify row-major access
                    }
                    if (auto *colLoop = llvm::dyn_cast<llvm::PHINode>(colIdx)) {
                        // Identify column-major access
                    }
                }
            }
        }
    }
}

void MatrixAnalysisPass::identifyOptimizationOpportunities(llvm::Function &F) {
    for (auto &BB : F) {
        for (auto &I : BB) {
            if (auto *mul = llvm::dyn_cast<llvm::BinaryOperator>(&I)) {
                if (mul->getOpcode() == llvm::Instruction::Mul) {
                    // Identify matrix multiplication patterns for PIM optimization
                    auto *LHS = mul->getOperand(0);
                    auto *RHS = mul->getOperand(1);
                    
                    if (auto *loadLHS = llvm::dyn_cast<llvm::LoadInst>(LHS)) {
                        if (auto *loadRHS = llvm::dyn_cast<llvm::LoadInst>(RHS)) {
                            // Found matrix element multiplication
                            // Mark for PIM-specific optimization
                        }
                    }
                }
            }
        }
    }
}

void MatrixAnalysisPass::collectMatrixInfo(llvm::Function &F) {
    matrices.clear();
    
    // Analyze function parameters to identify matrix dimensions
    for (auto &arg : F.args()) {
        if (arg.getType()->isPointerTy()) {
            MatrixInfo info;
            info.name = arg.getName().str();
            info.isInput = true;
            
            // Extract matrix dimensions from type information
            if (auto *arrayTy = llvm::dyn_cast<llvm::ArrayType>(arg.getType()->getPointerElementType())) {
                info.rows = arrayTy->getNumElements();
                if (auto *innerArrayTy = llvm::dyn_cast<llvm::ArrayType>(arrayTy->getElementType())) {
                    info.cols = innerArrayTy->getNumElements();
                    matrices.push_back(info);
                }
            }
        }
    }
}

bool MatrixAnalysisPass::validateMatrixOperation(const MatrixInfo &A, const MatrixInfo &B) {
    // Validate matrix dimensions for multiplication
    return A.cols == B.rows;
}

} // namespace pim_compiler