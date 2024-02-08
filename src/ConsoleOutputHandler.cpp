#include <cmath>

#include "ConsoleOutputHandler.h"
#include "Debug.h"
#include "LSDLE.h"


const float ConsoleOutputHandler::VERTICAL_SPACE_MODIFIER = 1.5;

// Constructors / Deconstructor 

ConsoleOutputHandler::ConsoleOutputHandler() {}

ConsoleOutputHandler::ConsoleOutputHandler(uint16_t _start_x, uint16_t _start_y, 
    uint16_t _end_x, uint16_t _end_y)
{
    text_display_handler = TextDisplayHandler();
    start_x = _start_x;
    start_y = _start_y;
    end_x = _end_x;
    end_y = _end_y;

    // Get the scaled font dimensions
    font_width = text_display_handler.get_scaled_font_width();
    font_height = text_display_handler.get_scaled_font_height();

    // Calculate the screen width in characters
    screen_character_width = (end_x - start_x)
        / font_width;

    if(screen_character_width < 30)
    {
        Debug::log("ConsoleOutputHandler::ConsoleOutputHandler() : Screen "
        "character width too small (< 30)", Debug::ERR);
        exit(0);
    }
}


// Public

void ConsoleOutputHandler::move_cursor(uint16_t x, uint16_t y)
{
    // If the cursor position is not within the window limits
    if(x < 0 || x > screen_character_width && y < 0 && y > 
        screen_character_height) return;

    cursor_position.first = x;
    cursor_position.second = y;
}

void ConsoleOutputHandler::move_cursor_x(uint16_t x)
{
    if (x < 0 || x > screen_character_width) return;

    cursor_position.first = x;
}

void ConsoleOutputHandler::move_cursor_y(uint16_t y)
{
    if(y < 0 || y > screen_character_height) return;

    cursor_position.second = y;
}   

void ConsoleOutputHandler::modify_cursor_position(uint16_t x_modify, 
    uint16_t y_modify)
{
    while(cursor_position.first + x_modify > screen_character_width)
    {
        x_modify -= screen_character_width + 1;
        ++y_modify;
    }

    // exit(0);

    cursor_position.first += x_modify;
    cursor_position.second += y_modify;
}

void ConsoleOutputHandler::add_ch(char c)
{
    _add_ch(c);
}

void ConsoleOutputHandler::add_ch(char c, std::string color)
{
    _add_ch(c, color);
}

void ConsoleOutputHandler::add_str(std::string str)
{
    _add_str(str);
}

void ConsoleOutputHandler::add_str(std::string str, std::string color)
{
    _add_str(str, color);
}

void ConsoleOutputHandler::add_new_line(uint8_t num)
{
    // Increment the y position of the cursor
    cursor_position.second += num;

    // Place the cursor at the x position that is set by the anchor
    cursor_position.first = anchor;
}

void ConsoleOutputHandler::clear_buffer()
{
    text_display_handler.clear_buffer();
}

void ConsoleOutputHandler::reset_cursor_position() 
{ 
    cursor_position = {0, 0};
}

void ConsoleOutputHandler::render()
{
    text_display_handler.render();
    reset_cursor_position();
    anchor = 0;
}

void ConsoleOutputHandler::set_anchor(uint16_t _anchor)
{
    if(anchor > screen_character_width)
    {
        anchor = screen_character_width;
        return;
    }

    anchor = _anchor;
}

const std::pair<uint16_t, uint16_t>& ConsoleOutputHandler::
    get_cursor_position() const { return cursor_position; }

TextDisplayHandler* ConsoleOutputHandler::get_text_display_handler()
    { return &text_display_handler; } 


// Private

void ConsoleOutputHandler::_add_ch(char c, std::string color)
{
    if(c == '\n')
    {
        add_new_line();
        return;
    }

    if(c == ' ')
    {
        ++cursor_position.first;
        // If the cursor is now off the screen
        if(cursor_position.first > screen_character_width)
        {
            // Place the cursor on the next line
            add_new_line();
        }

        return;
    }

    int x = start_x + (cursor_position.first * font_width);
    int y = start_y + std::ceil((
        cursor_position.second * font_height) * VERTICAL_SPACE_MODIFIER);

    // Add the character to the TextDisplayHandler
    text_display_handler.add_ch(c, 
        start_x + (cursor_position.first * font_width), 
        start_y + std::ceil((
        cursor_position.second * font_height) * VERTICAL_SPACE_MODIFIER),
        color);
    
    // Increment the cursor's position
    ++cursor_position.first;

    // If the cursor is now off the screen
    if(cursor_position.first > screen_character_width)
    {
        // Place the cursor on the next line
        add_new_line();
    }
}

void ConsoleOutputHandler::_add_str(std::string str, std::string color)
{
    for(char c : str)
    {
        _add_ch(c, color);
    }
}
