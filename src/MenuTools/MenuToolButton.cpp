#include "MenuToolButton.h"
#include "MenuToolItemType.h"

// Constructors / Deconstructor

MenuToolButton::MenuToolButton() : MenuToolItem()
{
    item_type = BUTTON;
}

MenuToolButton::MenuToolButton(Window* _window, std::string _name, std::string _cursor_color, 
    std::string _button_color)
    : MenuToolItem(_window, _cursor_color, BUTTON)
{
    name = _name;
    button_color = _button_color;
}


// Public

void MenuToolButton::render_no_status() const
{
    uint16_t initial_c_o_cursor_x_pos = 
        window->get_cursor_position().first;

    window->modify_cursor_position(3, 0);
    window->add_ch('[', button_color);
    window->add_str(name, button_color);
    window->add_ch(']', button_color);
    window->set_cursor_x_position(
        initial_c_o_cursor_x_pos);
    window->modify_cursor_position(0, 1);
}

void MenuToolButton::render_hovered() const 
{
    uint16_t initial_c_o_cursor_x_pos = 
        window->get_cursor_position().first;

    window->add_ch(' ');
    window->add_ch('>', cursor_color);
    window->add_ch(' ');
    window->add_ch('[', button_color);
    window->add_str(name, button_color);
    window->add_ch(']', button_color);
    window->set_cursor_x_position(
        initial_c_o_cursor_x_pos);
    window->modify_cursor_position(0, 1);
}

void MenuToolButton::render_selected() const
{
    uint16_t initial_c_o_cursor_x_pos = 
        window->get_cursor_position().first;

    window->add_ch(' ');
        window->add_ch('>', cursor_color);
        window->add_ch(' ');
        window->add_ch('[', cursor_color);
        window->add_str(name, button_color);
        window->add_ch(']', cursor_color);
        window->set_cursor_x_position(
            initial_c_o_cursor_x_pos);
        window->modify_cursor_position(0, 1);
}

MenuToolItem::Status MenuToolButton::handle_input()
{   
    // Simply return hovered, since we want to de select the button the frame
    // after it has been selected

    return HOVERED;
}
