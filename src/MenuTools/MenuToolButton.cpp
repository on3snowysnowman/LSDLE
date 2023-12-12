#include "MenuToolButton.h"
#include "MenuToolItemType.h"

// Constructors / Deconstructor

MenuToolButton::MenuToolButton() : MenuToolItem()
{
    item_type = BUTTON;
}

MenuToolButton::MenuToolButton(ConsoleOutputHandler* _console_output_handler,
    InputHandler* _input_handler, std::string _name, std::string _cursor_color, 
    std::string _button_color)
    : MenuToolItem(_console_output_handler, _input_handler, _cursor_color, 
    BUTTON)
{
    name = _name;
    button_color = _button_color;
}


// Public

void MenuToolButton::render_no_status() const
{
    uint16_t initial_c_o_cursor_x_pos = 
        console_output_handler->get_cursor_position().first;

    console_output_handler->modify_cursor_position(3, 0);
        console_output_handler->add_ch('[', button_color);
        console_output_handler->add_str(name, button_color);
        console_output_handler->add_ch(']', button_color);
        console_output_handler->move_cursor_x(
            initial_c_o_cursor_x_pos);
        console_output_handler->modify_cursor_position(0, 1);
}

void MenuToolButton::render_hovered() const 
{
    uint16_t initial_c_o_cursor_x_pos = 
        console_output_handler->get_cursor_position().first;

    console_output_handler->add_ch(' ');
        console_output_handler->add_ch('>', cursor_color);
        console_output_handler->add_ch(' ');
        console_output_handler->add_ch('[', button_color);
        console_output_handler->add_str(name, button_color);
        console_output_handler->add_ch(']', button_color);
        console_output_handler->move_cursor_x(
            initial_c_o_cursor_x_pos);
        console_output_handler->modify_cursor_position(0, 1);
}

void MenuToolButton::render_selected() const
{
    uint16_t initial_c_o_cursor_x_pos = 
        console_output_handler->get_cursor_position().first;

    console_output_handler->add_ch(' ');
        console_output_handler->add_ch('>', cursor_color);
        console_output_handler->add_ch(' ');
        console_output_handler->add_ch('[', cursor_color);
        console_output_handler->add_str(name, button_color);
        console_output_handler->add_ch(']', cursor_color);
        console_output_handler->move_cursor_x(
            initial_c_o_cursor_x_pos);
        console_output_handler->modify_cursor_position(0, 1);
}

MenuToolItem::Status MenuToolButton::handle_input()
{   
    // Simply return hovered, since we want to de select the button the frame
    // after it has been selected

    return HOVERED;
}
