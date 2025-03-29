#ifndef LOOP_ANALYZER_H
#define LOOP_ANALYZER_H

#include <vector>
#include <string>
#include "parser.h"

struct AnalyzedLoop {
    std::string loopHeader;
    bool isParallelizable;
    std::vector<std::string> dependencies;
};

std::vector<AnalyzedLoop> analyzeLoops(const ParsedCode &parsedCode);

#endif // LOOP_ANALYZER_H