#include "BaseComponent.h"


// Constructors / Deconstructor

BaseComponent::BaseComponent() : id(get_next_id()), component_type(TEXT) {}

BaseComponent::BaseComponent(ComponentType _component_type)
    : id(get_next_id()), component_type(_component_type) {}

// Public

void BaseComponent::handle_instruction(InstructionChain i_chain) noexcept
{}

uint64_t BaseComponent::get_id() const noexcept{ return id; }

void BaseComponent::add_post_instruction_chain(InstructionChain i_chain) 
    noexcept
{
    // Iterate throught the InstructionChain, and add each instruction to a 
    // vector to make them permanent, and so they do not pop out of the queue
    // when fetched.
    while(!i_chain.empty())
    {
        post_instruction_i_chain.push_back(i_chain.get_next_instruction());
    }
}

// Protected

void BaseComponent::execute_post_instruction_chain() noexcept {}

// Private

uint64_t BaseComponent::get_next_id() noexcept
{
    static uint64_t next_id = 0;

    return next_id++;
}
