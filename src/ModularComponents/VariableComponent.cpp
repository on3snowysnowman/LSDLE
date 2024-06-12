#include "VariableComponent.h"
#include "LStringManip.h"
#include "LMath.h"

// Constructors / Deconstructor 

VariableComponent::VariableComponent() : BaseComponent(VARIABLE) {}

VariableComponent::VariableComponent(int _content) : BaseComponent(VARIABLE),
    content(_content) {}

// Public

void VariableComponent::handle_instruction(InstructionChain i_chain) 
    noexcept
{
    while(!i_chain.empty())
    {
        (this->*instructions_to_functions.at(
            i_chain.get_next_instruction()))(i_chain);
    }
}

int VariableComponent::get_content() const noexcept
{ return content; }

// Private

void VariableComponent::handle_modify_instruction(InstructionChain& i_chain) 
{
    content = LSDLELIB::handle_int32_addition(content, 
        LSDLELIB::string_to_int32(i_chain.get_next_instruction()));
}

void VariableComponent::handle_set_instruction(InstructionChain& i_chain) 
{
    content = LSDLELIB::string_to_int32(i_chain.get_next_instruction());
}

void VariableComponent::execute_post_instruction_chain() noexcept
{
    for(std::vector<std::string>::const_iterator it = 
        post_instruction_i_chain.begin(); it < post_instruction_i_chain.end();
        ++it)
    {
        if((*it) == "Max") 
        {
            // Iterator is advanced so the next function gets the next item, 
            // not this one
            handle_max_instruction(++it);
        }

        // else: (*it) == "Min"

        handle_min_instruction(++it);
    }
}

void VariableComponent::handle_max_instruction(
    std::vector<std::string>::const_iterator& it) noexcept
{
    // Get the max limit for this Component from the next instruction 
    int max_limit = LSDLELIB::string_to_int32(*it);

    // Set the content to the max if it exceeds it
    content = LSDLELIB::round_num_to_maximum(content, max_limit);
}

void VariableComponent::handle_min_instruction(
    std::vector<std::string>::const_iterator& it) noexcept
{
    // Get the min limit for this Component from the next instruction
    int min_limit = LSDLELIB::string_to_int32(*it);

    // Set the content to the  min if it preceeds it
    content = LSDLELIB::round_num_to_minimum(content, min_limit);
}
