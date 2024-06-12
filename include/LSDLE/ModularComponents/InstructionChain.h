#pragma once

#include <string>
#include <queue>
#include <initializer_list>


struct InstructionChain
{
    InstructionChain(std::queue<std::string> _chain) { chain = _chain; }

    InstructionChain(std::initializer_list<std::string> instructions)
    {
        for(const std::string& str : instructions)
        {
            chain.push(str);
        }
    }

    bool empty() const noexcept
    {
        return chain.empty();
    }

    std::string get_next_instruction()
    {
        if(chain.empty()) return "";

        std::string* next = &chain.front();

        chain.pop();

        return *next;
    }

    std::queue<std::string> chain;
};