#pragma once

#include <cstdint>
#include <vector>

#include "InstructionChain.h"

enum ComponentType
{
    VARIABLE, 
    TEXT
};


class BaseComponent
{

public:

    BaseComponent();

    BaseComponent(ComponentType component_type);

    virtual void handle_instruction(InstructionChain i_chain) noexcept;

    void add_reference(uint64_t component_id) noexcept;

    void add_post_instruction_chain(InstructionChain i_chain) noexcept;

    uint64_t get_id() const noexcept;

protected:

    // Type of this Component
    const ComponentType component_type;

    // Unique ID of this Component 
    const uint64_t id;

    /**
     * List of instructions that will execute after each time this variable 
     * is requested to handled a passed instruction chain. This chain can be 
     * used to clamp variables down to a maximum number for instance, after they 
     * may have been modified past the target limit 
     * */
    std::vector<std::string> post_instruction_i_chain;

    std::vector<uint64_t> references;

    virtual void execute_post_instruction_chain() noexcept;

private:

    static uint64_t get_next_id() noexcept;
};
