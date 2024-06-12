#include "ListComponent.h"
#include "TextComponent.h"
#include "VariableComponent.h"
#include "LStringManip.h"

// Constructors / Deconstructor

ListComponent::ListComponent() : BaseComponent(LIST) {}


// Public

void ListComponent::handle_instruction(InstructionChain i_chain) noexcept
{
    while(!i_chain.empty())
    {
        (this->*instructions_to_functions.at(
            i_chain.get_next_instruction()))(i_chain);
    }
}

const std::vector<BaseComponent*>& ListComponent::get_content() const noexcept
{ return content; }


// Private

void ListComponent::handle_add_component_instruction(InstructionChain& i_chain)
    noexcept
{
    // Get type of Component to be added
    std::string instruction = i_chain.get_next_instruction();

    if(instruction == "Text")
    {
        // Add a new Text Component initiated with the value of the next 
        // instruction
        content.push_back(new TextComponent(i_chain.get_next_instruction()));
    }

    else if(instruction == "Variable")
    {
        // Add a new Variable Component initiated with the value of the next
        // instruction
        content.push_back(new VariableComponent(
            LSDLELIB::string_to_int32(i_chain.get_next_instruction())));
    }

    else
    {
        content.push_back(new ListComponent());
    }
}

void ListComponent::handle_insert_component_instruction(
    InstructionChain& i_chain) noexcept
{
    // TODO : Replace stoi with LMath integer conversion
    int index = LSDLELIB::string_to_int32(i_chain.get_next_instruction());

    // Get type of Component to be added
    std::string instruction = i_chain.get_next_instruction();

    if(instruction == "Text")
    {
        content.insert(content.begin() + index, 
            new TextComponent(i_chain.get_next_instruction()));
    }

    else if(instruction == "Variable")
    {
        content.insert(content.begin() + index, 
            new VariableComponent(
                LSDLELIB::string_to_int32(i_chain.get_next_instruction())));
    }

    else
    {
        content.insert(content.begin() + index, new ListComponent());
    }
}

void ListComponent::handle_remove_component_instruction(
    InstructionChain& i_chain) noexcept
{
    // Get the type of Component to remove
    std::string instruction = i_chain.get_next_instruction();

    if(instruction == "Text") 
    {
        // Get the target id of the Text that should be removed
        instruction = i_chain.get_next_instruction();

        remove_component(LSDLELIB::string_to_uint64(instruction));
        return;
    }

    else if(instruction == "Variable") {}

    // Instruction == "List"
    else
    {
        
    }
}  

void ListComponent::remove_component(uint64_t target_id)
{
    for(std::vector<BaseComponent*>::iterator it = content.begin();
        it != content.end(); ++it)
    {
        // if((*it)->get_id() == target_id)
        // {
        //     content.erase()
        // }
    }
}


