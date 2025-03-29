#include "pim_memory_mapper.h"
#include <bitset>
#include <algorithm>
#include <unordered_map>

// Lookup table for common memory access patterns
const std::unordered_map<std::string, std::string> MEMORY_PATTERN_LOOKUP = {
    {"sequential", "1010101010101010"},
    {"strided", "1000100010001000"},
    {"random", "1100101011001010"},
    {"block", "1111000011110000"}
};

MappedMemory mapMemory(const std::vector<AnalyzedLoop> &analyzedLoops) {
    MappedMemory result;
    
    for (const auto &loop : analyzedLoops) {
        if (!loop.isParallelizable) continue;
        
        // Generate memory access patterns for parallel loops
        for (const auto &access : loop.dependencies) {
            // Try to find pattern in lookup table first
            auto it = MEMORY_PATTERN_LOOKUP.find(access.patternType);
            if (it != MEMORY_PATTERN_LOOKUP.end()) {
                result.memoryAccesses.push_back(it->second);
            } else {
                // Fallback to dynamic pattern generation
                std::bitset<16> pattern;
                for (size_t i = 0; i < 16; i++) {
                    pattern[i] = (i % 2 == 0);
                }
                result.memoryAccesses.push_back(pattern.to_string());
            }
            
            result.pimAddresses.push_back("0x" + std::to_string(result.memoryAccesses.size()));
            result.isParallelAccess.push_back(true);
        }
    }
    
    return result;
}