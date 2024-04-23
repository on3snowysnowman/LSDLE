#include "DelayedTextHandler.h"
#include "LSDLE.h"
#include "LMath.h"


// Constructors / Deconstructor

DelayedTextHandler::DelayedTextHandler(uint16_t start_x, uint16_t start_y, uint16_t end_x, 
    uint16_t end_y) 
{
    coh = new ConsoleOutputHandler(start_x, start_y, end_x, end_y);
}


// Public

void DelayedTextHandler::update() noexcept
{
    for(std::list<DelayedText>::iterator it = content.begin();
        it != content.end(); ++it)
    {
        DelayedText& _text = (*it);
     
        // The current char that is done being delayed,and should be fully 
        // rendered
        if(_text.render_complete)
        {
            coh->add_str(_text.text.content, _text.text.color);

            --_text.lifetime;
            if(_text.lifetime == 0)
            {
                content.erase(it);
                --it;
            }

            continue;
        }
        
        coh->add_str(_text.text.content.substr(0, _text.current_char_index), 
            _text.text.color);

        // Iterate through the rest of the string to parse for new line 
        // characters
        for(uint16_t i = _text.current_char_index + 1; 
            i < _text.text.content.size(); ++i)
        {
            if(_text.text.content.at(i) == '\n')
            {
                coh->add_new_line();
            }
        }

        // Increase the delay count of this text item
        ++_text.current_delay_count;

        // If the delay that is waited in between increasing the number of
        // characters are rendered reaches the amount needed to delay
        if(_text.current_delay_count == delay_between_rendering)
        {
            // Set the delay back to 0 frames
            _text.current_delay_count = 0;

            // Increase the character count of the string
            ++_text.current_char_index;

            // If the end of the string has been reached
            if(_text.current_char_index == _text.text.content.size())
            {
                // On the next render cycle flag this str to simply be rendered
                // whole
                _text.render_complete = true;
            }
        }

        --_text.lifetime;
        if(_text.lifetime == 0)
        {
            content.erase(it);
            --it;
        }
    }
}

void DelayedTextHandler::add_str(std::string _str, std::string color,
    uint16_t lifetime) noexcept
{
    content.push_back(DelayedText
        {false, 0, lifetime, 0, ColorString(_str, color)});
}

void DelayedTextHandler::add_new_line(uint8_t num_new_line)
{
    std::string str_new_line;

    for(uint8_t i = 0; i < num_new_line; ++i)
    {
        str_new_line.push_back('\n');
    }
}


// Private
