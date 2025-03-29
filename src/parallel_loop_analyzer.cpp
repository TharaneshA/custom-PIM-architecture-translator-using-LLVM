#include "parallel_loop_analyzer.h"
#include <vector>
#include <algorithm>
#include <unordered_map>

// Lookup table for common loop dependency patterns
const std::unordered_map<std::string, bool> DEPENDENCY_PATTERN_LOOKUP = {
    {"independent", true},
    {"flow", false},
    {"anti", false},
    {"output", false},
    {"reduction", true}
};

std::vector<AnalyzedLoop> analyzeLoops(const ParsedCode &parsedCode) {
    std::vector<AnalyzedLoop> result;
    
    for (const auto &loop : parsedCode.loops) {
        AnalyzedLoop analyzedLoop;
        analyzedLoop.loopHeader = loop;
        
        // Initialize as parallelizable unless dependencies found
        analyzedLoop.isParallelizable = true;
        
        // Check dependencies against lookup table
        for (const auto &access : parsedCode.memoryAccesses) {
            auto it = DEPENDENCY_PATTERN_LOOKUP.find(access.patternType);
            if (it != DEPENDENCY_PATTERN_LOOKUP.end()) {
                analyzedLoop.dependencies.push_back(access);
                analyzedLoop.isParallelizable = it->second;
            } else {
                // Fallback to default analysis
                if (access.find(loop) != std::string::npos) {
                    analyzedLoop.dependencies.push_back(access);
                    analyzedLoop.isParallelizable = false;
                }
            }
        }
        
        result.push_back(analyzedLoop);
    }
    
    return result;
}