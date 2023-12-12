#include "MenuToolText.h"
#include "MenuToolItemType.h"

// Constructors / Deconstructor

MenuToolText::MenuToolText() 
{
    item_type = TEXT;
}

MenuToolText::MenuToolText(ConsoleOutputHandler* _console_output_handler,
    InputHandler* _input_handler, std::string _cursor_color, 
    std::string _content) :
    MenuToolItem(_console_output_handler, _input_handler, _cursor_color, TEXT)
{
    content = _content;
}


// Public

void MenuToolText::render_no_status() const
{
    uint16_t initial_c_o_cursor_x_pos = 
        console_output_handler->get_cursor_position().first;

    console_output_handler->modify_cursor_position(3, 0);
    console_output_handler->add_str(content);
    console_output_handler->move_cursor_x(
            initial_c_o_cursor_x_pos);
    console_output_handler->modify_cursor_position(0, 1);
}

void MenuToolText::render_hovered() const
{
    uint16_t initial_c_o_cursor_x_pos = 
        console_output_handler->get_cursor_position().first;

    console_output_handler->add_ch(' ');
    console_output_handler->add_ch('>', cursor_color);
    console_output_handler->add_ch(' ');
    console_output_handler->add_str(content);
    console_output_handler->move_cursor_x(
            initial_c_o_cursor_x_pos);
    console_output_handler->modify_cursor_position(0, 1);
}

void MenuToolText::render_selected() const
{
    uint16_t initial_c_o_cursor_x_pos = 
        console_output_handler->get_cursor_position().first;

        console_output_handler->add_str("  ");
        console_output_handler->add_ch('>', cursor_color);
        console_output_handler->add_ch(' ');
        console_output_handler->add_str(content, cursor_color);
        console_output_handler->add_ch('_');
        console_output_handler->move_cursor_x(
            initial_c_o_cursor_x_pos);
    console_output_handler->modify_cursor_position(0, 1);
}

MenuToolItem::Status MenuToolText::handle_input() 
{
    // Initialize default status, which is selected since we are handling input
    Status status = SELECTED;

    // Get the raw pressed keys 
    std::vector<uint32_t> keys = input_handler->get_raw_keys();

    for(uint32_t key : keys)
    {
        // Enter key is pressed
        if(key == SDLK_RETURN)
        {
            // Block the Enter key and deselect the Text by returning a 
            // HOVERED status 
            input_handler->block_key_until_released(SDLK_RETURN);
            return HOVERED;
        }

        // Key is not the Enter key

        // Apply the input to the string if applicable
        apply_input_to_string(key, content);

    }

    return status;
}
