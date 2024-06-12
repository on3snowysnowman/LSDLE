#pragma once

#include <unordered_map>

#include "BaseComponent.h"

class VariableComponent : public BaseComponent
{

public:

    VariableComponent();

    VariableComponent(int content);

    void handle_instruction(InstructionChain i_chain) noexcept final;

    int get_content() const noexcept;

private:

    using function_ptr = void (VariableComponent::*)(InstructionChain&);

    const std::unordered_map<std::string, function_ptr>
        instructions_to_functions
    {
        {"Modify", &VariableComponent::handle_modify_instruction},
        {"Set", &VariableComponent::handle_set_instruction}
    };

    int content {};
    
    void handle_modify_instruction(InstructionChain& i_chain);

    void handle_set_instruction(InstructionChain& i_chain);
    
    void execute_post_instruction_chain() noexcept final;

    void handle_max_instruction(std::vector<std::string>::const_iterator& it)
        noexcept;
 
    void handle_min_instruction(std::vector<std::string>::const_iterator& it)
        noexcept;
}; 