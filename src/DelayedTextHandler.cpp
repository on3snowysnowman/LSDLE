#include "DelayedTextHandler.h"


// Constructors / Deconstructor

DelayedTextHandler::DelayedTextHandler(uint16_t start_x, uint16_t start_y, uint16_t end_x, 
    uint16_t end_y) 
{
    coh = new ConsoleOutputHandler(start_x, start_y, end_x, end_y);

    
}


// Public

void DelayedTextHandler::update() noexcept
{
    for(DelayedText& _text : content)
    {
        _text
    }
}


// Private
