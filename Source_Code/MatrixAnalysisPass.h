#ifndef MATRIX_ANALYSIS_PASS_H
#define MATRIX_ANALYSIS_PASS_H

#include <llvm/Pass.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>
#include <vector>

namespace pim_compiler {

class MatrixAnalysisPass : public llvm::ModulePass {
public:
    static char ID;
    MatrixAnalysisPass() : ModulePass(ID) {}

    bool runOnModule(llvm::Module &M) override;
    void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;

    // Matrix analysis methods
    bool detectMatrixOperations(llvm::Function &F);
    void analyzeAccessPatterns(llvm::Function &F);
    void identifyOptimizationOpportunities(llvm::Function &F);

private:
    struct MatrixInfo {
        unsigned rows;
        unsigned cols;
        std::string name;
        bool isInput;
    };

    std::vector<MatrixInfo> matrices;
    void collectMatrixInfo(llvm::Function &F);
    bool validateMatrixOperation(const MatrixInfo &A, const MatrixInfo &B);
};

} // namespace pim_compiler

#endif // MATRIX_ANALYSIS_PASS_H