#pragma once

#include <string>

#include "BaseComponent.h"

class TextComponent : public BaseComponent
{

public:

    TextComponent();

    TextComponent(std::string content);

    void handle_instruction(InstructionChain i_chain) noexcept final;

    const std::string& get_content() const noexcept;

private:

    std::string content;

    void execute_post_instruction_chain() noexcept final;
};
