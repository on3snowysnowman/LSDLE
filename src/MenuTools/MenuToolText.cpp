#include "MenuToolText.h"
#include "MenuToolItemType.h"

// Constructors / Deconstructor

MenuToolText::MenuToolText() 
{
    item_type = TEXT;
}

MenuToolText::MenuToolText(Window* _window, std::string _cursor_color, 
    std::string _content) :MenuToolItem(_window, _cursor_color, TEXT)
{
    content = _content;
}


// Public

void MenuToolText::render_no_status() const
{
    uint16_t initial_c_o_cursor_x_pos = 
        window->get_cursor_position().first;

    window->modify_cursor_position(3, 0);
    window->add_str(content);
    window->set_cursor_x_position(
            initial_c_o_cursor_x_pos);
    window->modify_cursor_position(0, 1);
}

void MenuToolText::render_hovered() const
{
    uint16_t initial_c_o_cursor_x_pos = 
        window->get_cursor_position().first;

    window->add_ch(' ');
    window->add_ch('>', cursor_color);
    window->add_ch(' ');
    window->add_str(content);
    window->set_cursor_x_position(
            initial_c_o_cursor_x_pos);
    window->modify_cursor_position(0, 1);
}

void MenuToolText::render_selected() const
{
    uint16_t initial_c_o_cursor_x_pos = 
        window->get_cursor_position().first;

        window->add_str("  ");
        window->add_ch('>', cursor_color);
        window->add_ch(' ');
        window->add_str(content, cursor_color);
        window->add_ch('_');
        window->set_cursor_x_position(
            initial_c_o_cursor_x_pos);
    window->modify_cursor_position(0, 1);
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
