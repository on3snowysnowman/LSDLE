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

    void add_str(std::string _str, std::string color, 
        uint16_t liftime = ) noexcept;

    void add_new_line(uint8_t num_new_line = 1) noexcept;

private:

    struct DelayedText
    {
        // If this Text has been fully rendered over the delayed frames
        bool render_complete {};

        uint16_t current_char_index {};

        // Frame timestamp that this item will exist until
        uint16_t lifetime {};

        uint8_t current_delay_count {};

        ColorString text; // Content of the DelayedText item
    };

    // Number of frames delayed between rendering each character of a Text item
    uint8_t delay_between_rendering {4};

    std::list<DelayedText> content;

    ConsoleOutputHandler* coh;

};
