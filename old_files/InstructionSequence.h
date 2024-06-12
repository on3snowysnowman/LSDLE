#pragma once

#include <string>
#include <queue>

/**
 * @brief The InstructionSequence struct is purely a storage struct. 
 * 
 * The IS can be filled with strings that are treated as "instruction 
 * sequences" by many modular processes.
 */
struct InstructionSequence
{

    InstructionSequence(const std::queue<std::string>& _instructions)
    {
        instructions = _instructions;
    }

    std::queue<std::string> instructions;
};