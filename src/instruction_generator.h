#ifndef INSTRUCTION_GENERATOR_H
#define INSTRUCTION_GENERATOR_H

#include <vector>
#include <string>
#include "memory_mapper.h"

std::vector<std::string> generateInstructions(const MappedMemory &mappedMemory);

#endif // INSTRUCTION_GENERATOR_H