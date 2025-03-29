#ifndef MEMORY_MAPPER_H
#define MEMORY_MAPPER_H

#include <vector>
#include <string>
#include "parallel_loop_analyzer.h"

enum class OperationType {
    LOAD,
    STORE,
    ADD,
    MULTIPLY
};

struct MemoryOperation {
    OperationType type;
    std::bitset<16> memory_access_pattern;
};

struct MappedMemory {
    std::vector<std::string> memoryAccesses;
    std::vector<std::string> pimAddresses;
    std::vector<bool> isParallelAccess;
    std::vector<MemoryOperation> operations;
};

MappedMemory mapMemory(const std::vector<AnalyzedLoop> &analyzedLoops);

#endif // MEMORY_MAPPER_H