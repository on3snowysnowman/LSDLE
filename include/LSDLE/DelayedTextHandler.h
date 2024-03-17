#pragma once

#include "ConsoleOutputHandler.h"
#include "ColorString.h"

#include <list>

class DelayedTextHandler
{

public:

    DelayedTextHandler(uint16_t start_x, uint16_t start_y, uint16_t end_x, 
        uint16_t end_y);

    void update();

private:

    struct DelayedTest
    {
        // The frame number this 
        uint64_t frame_stamp;

    };

    // List of strings
    std::list<ColorString> content;

    ConsoleOutputHandler* coh;

};
