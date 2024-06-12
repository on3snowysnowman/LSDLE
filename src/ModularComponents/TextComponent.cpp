#include "TextComponent.h"


// Constructors / Deconstructor

TextComponent::TextComponent() : BaseComponent(TEXT) {}

TextComponent::TextComponent(std::string _content) : BaseComponent(TEXT), 
    content(_content) {}


// Public

void TextComponent::handle_instruction(InstructionChain i_chain) noexcept
{
    // There is only one instruction that can be passed to the TextComponent,
    // the "set" instruction. There is no checking needed to see what type of
    // instruction is passed

    // Skip this instruction since it is known that it is just the "set" 
    // command
    i_chain.get_next_instruction();

    // Set the content to the next instruction, which is the content that the 
    // user wants
    content = i_chain.get_next_instruction();
}

const std::string& TextComponent::get_content() const noexcept
{ return content; }


// Private

void TextComponent::execute_post_instruction_chain() noexcept
{
    // This function is only defined to final the virtual function from the 
    // base class. It is empty because there are no post processing 
    // instructions available for the TextComponent
}
