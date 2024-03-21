#pragma once

#include "ConsoleOutputHandler.h"
#include "ColorString.h"

#include <list>
#include <unordered_map>

class DelayedTextHandler
{

public:

    DelayedTextHandler(uint16_t start_x, uint16_t start_y, uint16_t end_x, 
        uint16_t end_y);

    void update() noexcept;

private:

    struct DelayedText
    {
        // If this Text has been fully rendered over the delayed frames
        bool render_complete;

        uint16_t current_char_index {};

        // Number of frames this Text item will exist for 
        uint16_t lifetime {};
    };

    // Number of frames delayed between rendering each character of a Text item
    uint8_t delay_between_rendering {};

    std::list<DelayedText> content;

    ConsoleOutputHandler* coh;

};
