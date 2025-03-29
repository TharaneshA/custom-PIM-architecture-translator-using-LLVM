#include "instruction_generator.h"
#include "pim_memory_mapper.h"
#include <bitset>
#include <sstream>
#include <unordered_map>

// Lookup table for operation type to instruction bit mapping
const std::unordered_map<OperationType, std::bitset<5>> OPCODE_LOOKUP = {
    {OperationType::LOAD, std::bitset<5>("00001")},
    {OperationType::STORE, std::bitset<5>("00010")},
    {OperationType::ADD, std::bitset<5>("00011")},
    {OperationType::MULTIPLY, std::bitset<5>("00100")},
    {OperationType::SUBTRACT, std::bitset<5>("00101")},
    {OperationType::DIVIDE, std::bitset<5>("00110")},
    {OperationType::AND, std::bitset<5>("00111")},
    {OperationType::OR, std::bitset<5>("01000")},
    {OperationType::XOR, std::bitset<5>("01001")},
    {OperationType::NOT, std::bitset<5>("01010")},
    {OperationType::SHIFT_LEFT, std::bitset<5>("01011")},
    {OperationType::SHIFT_RIGHT, std::bitset<5>("01100")},
    {OperationType::COMPARE, std::bitset<5>("01101")},
    {OperationType::CONDITIONAL, std::bitset<5>("01110")},
    {OperationType::VECTOR_OP, std::bitset<5>("01111")}
};

std::vector<std::string> generateInstructions(const MappedMemory &mappedMemory) {
    std::vector<std::string> instructions;
    
    // Add PROG instruction with configuration bits (24-bit format: 00|CFG_BITS|0000000000000000)
    std::bitset<24> prog_instruction;
    prog_instruction[23] = 0;  // PROG type bit 1
    prog_instruction[22] = 0;  // PROG type bit 0
    
    // Set configuration bits (bits 21-16)
    prog_instruction[21] = mappedMemory.config.batch_processing;
    prog_instruction[20] = mappedMemory.config.pipelining;
    prog_instruction[19] = mappedMemory.config.parallel_execution;
    prog_instruction[18] = mappedMemory.config.error_correction;
    prog_instruction[17] = mappedMemory.config.power_saving;
    prog_instruction[16] = mappedMemory.config.debug_mode;
    
    // Convert to string
    std::stringstream prog_ss;
    for (int i = 23; i >= 0; i--) {
        prog_ss << (prog_instruction[i] ? '1' : '0');
    }
    instructions.push_back(prog_ss.str());
    
    // Generate EXE instructions for each matrix operation
    for (const auto &op : mappedMemory.operations) {
        std::bitset<24> instruction;
        
        // Set instruction type to EXE (01)
        instruction[23] = 0;
        instruction[22] = 1;
        
        // Set operation type bits (bits 20-16) using lookup table
        auto it = OPCODE_LOOKUP.find(op.type);
        if (it != OPCODE_LOOKUP.end()) {
            instruction[20] = it->second[4];
            instruction[19] = it->second[3];
            instruction[18] = it->second[2];
            instruction[17] = it->second[1];
            instruction[16] = it->second[0];
        }
        
        // Set memory access bits (bits 15-0)
        instruction |= std::bitset<24>(op.memory_access_pattern.to_ulong());
        
        // Convert to 24-bit string
        std::stringstream ss;
        for (int i = 23; i >= 0; i--) {
            ss << (instruction[i] ? '1' : '0');
        }
        instructions.push_back(ss.str());
    }
    
    // Add END instruction with status bits (24-bit format: 10|STATUS_BITS|0000000000000000)
    std::bitset<24> end_instruction;
    end_instruction[23] = 1;  // END type bit 1
    end_instruction[22] = 0;  // END type bit 0
    
    // Set status bits (bits 21-16)
    end_instruction[21] = mappedMemory.status.success;
    end_instruction[20] = mappedMemory.status.error_flag;
    end_instruction[19] = mappedMemory.status.overflow_flag;
    end_instruction[18] = mappedMemory.status.underflow_flag;
    end_instruction[17] = mappedMemory.status.timeout_flag;
    end_instruction[16] = mappedMemory.status.debug_flag;
    
    // Convert to string
    std::stringstream end_ss;
    for (int i = 23; i >= 0; i--) {
        end_ss << (end_instruction[i] ? '1' : '0');
    }
    instructions.push_back(end_ss.str());
    
    return instructions;
}