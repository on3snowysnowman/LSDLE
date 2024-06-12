#pragma once

#include <vector>
#include <unordered_map>

#include "BaseComponent.h"

class ListComponent : public BaseComponent
{

public:

    ListComponent();

    void handle_instruction(InstructionChain i_chain) noexcept final;

    const std::vector<BaseComponent*>& get_content() const noexcept;

private:

    using function_ptr = void (ListComponent::*)(InstructionChain&);

    void handle_add_component_instruction(InstructionChain& i_chain) noexcept;

    void handle_insert_component_instruction(InstructionChain& i_chain) 
        noexcept;

    void handle_remove_component_instruction(InstructionChain& i_chain) 
        noexcept;

    void remove_component(uint64_t target_id);

    std::vector<BaseComponent*> content;

    const std::unordered_map<std::string, function_ptr> 
        instructions_to_functions
    {
        {"Add component", &ListComponent::handle_add_component_instruction},
        {"Insert component", &ListComponent::
            handle_insert_component_instruction},
        {"Remove component", 
            &ListComponent::handle_remove_component_instruction}
    };
};
