#ifndef MEMORY_MAPPER_H
#define MEMORY_MAPPER_H

#include <vector>
#include <string>
#include "loop_analyzer.h"

struct MappedMemory {
    std::vector<std::string> memoryAccesses;
    std::vector<std::string> pimAddresses;
    std::vector<bool> isParallelAccess;
};

MappedMemory mapMemory(const std::vector<AnalyzedLoop> &analyzedLoops);

#endif // MEMORY_MAPPER_H