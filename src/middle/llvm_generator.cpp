#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include "../include/matrix.h"

using namespace llvm;

class LLVMGenerator {
public:
    LLVMGenerator() : Context(), Builder(Context) {
        Module = std::make_unique<Module>("matrix_mult", Context);
        setupMatrixMultFunction();
    }

    // Generate LLVM IR for matrix multiplication
    void generateMatrixMult(const pim::Matrix& lhs, const pim::Matrix& rhs) {
        // Create matrix dimensions as constants
        Value* rows = ConstantInt::get(Type::getInt64Ty(Context), lhs.rows());
        Value* cols = ConstantInt::get(Type::getInt64Ty(Context), rhs.cols());
        Value* common = ConstantInt::get(Type::getInt64Ty(Context), lhs.cols());

        // Allocate memory for matrices
        Value* lhsMem = createMatrixAlloca("lhs", rows, common);
        Value* rhsMem = createMatrixAlloca("rhs", common, cols);
        Value* resultMem = createMatrixAlloca("result", rows, cols);

        // Generate multiplication loops
        generateMultiplicationLoops(lhsMem, rhsMem, resultMem, rows, cols, common);
    }

private:
    LLVMContext Context;
    IRBuilder<> Builder;
    std::unique_ptr<Module> Module;
    Function* MatrixMultFunc;

    // Setup the main matrix multiplication function
    void setupMatrixMultFunction() {
        // Create function type
        std::vector<Type*> ParamTypes = {
            Type::getInt64Ty(Context),  // rows
            Type::getInt64Ty(Context),  // cols
            Type::getInt64Ty(Context)}; // common
        FunctionType* FT = FunctionType::get(
            Type::getVoidTy(Context), ParamTypes, false);
        
        // Create function
        MatrixMultFunc = Function::Create(
            FT, Function::ExternalLinkage, "matrix_mult", Module.get());
    }

    // Create memory allocation for a matrix
    Value* createMatrixAlloca(const std::string& name,
                             Value* rows, Value* cols) {
        // Calculate total size
        Value* size = Builder.CreateMul(rows, cols, "size");
        
        // Create allocation
        Type* Int32Ty = Type::getInt32Ty(Context);
        ArrayType* ArrayTy = ArrayType::get(Int32Ty, 0);
        return Builder.CreateAlloca(ArrayTy, size, name);
    }

    // Generate nested loops for matrix multiplication
    void generateMultiplicationLoops(Value* lhs, Value* rhs, Value* result,
                                   Value* rows, Value* cols, Value* common) {
        // TODO: Implement the three nested loops for matrix multiplication
        // TODO: Add memory mapping information for PIM architecture
        // TODO: Generate load/store instructions with proper memory access patterns
    }
};