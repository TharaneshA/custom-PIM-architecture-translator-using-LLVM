#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include "llvm/IR/Module.h"

struct ParsedCode {
    std::vector<std::string> functions;
    std::vector<std::string> loops;
    std::vector<std::string> memoryAccesses;
};

ParsedCode parseLLVMIR(const std::string &filename);

#endif // PARSER_H