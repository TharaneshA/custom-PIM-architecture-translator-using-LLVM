#include <iostream>
#include <fstream>
#include "llvm/Support/CommandLine.h"
#include "ir_parser.h"
#include "parallel_loop_analyzer.h"
#include "pim_memory_mapper.h"
#include "instruction_generator.h"

using namespace llvm;

static cl::opt<std::string> InputFilename(cl::Positional, cl::desc("<input .ll file>"), cl::Required);
static cl::opt<std::string> OutputFilename(cl::Positional, cl::desc("<output .isa file>"), cl::Required);

int main(int argc, char **argv) {
    cl::ParseCommandLineOptions(argc, argv, "PIM Compiler");
    
    // Parse LLVM IR
    auto parsedCode = parseLLVMIR(InputFilename);
    
    // Analyze loops for parallelization
    auto analyzedLoops = analyzeLoops(parsedCode);
    
    // Map memory accesses to PIM architecture
    auto mappedMemory = mapMemory(analyzedLoops);
    
    // Generate PIM ISA instructions
    auto isaInstructions = generateInstructions(mappedMemory);
    
    // Output results
    std::ofstream outFile(OutputFilename);
    for (const auto &instr : isaInstructions) {
        outFile << instr << "\n";
    }
    
    return 0;
}