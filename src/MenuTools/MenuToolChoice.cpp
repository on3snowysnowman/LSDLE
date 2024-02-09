#include "MenuToolChoice.h"


#include <iostream>

// Constructors / Deconstructor

MenuToolChoice::MenuToolChoice() : MenuToolItem() {}

MenuToolChoice::MenuToolChoice(Window* _window, std::string _cursor_color, std::string _name,
    uint8_t _choice_index) :
    MenuToolItem(_window, _cursor_color, CHOICE)
{
    name = _name;
    choice_index = _choice_index;
    cursor_index = choice_index;
}


// Public

void MenuToolChoice::render_no_status() const
{
    uint16_t initial_c_o_cursor_x_pos = 
        window->get_cursor_position().first;
    
    window->modify_cursor_position(3, 0);
    window->add_str(name);
    window->add_str(": ");
    window->add_str(choices.at(choice_index).content, 
        choices.at(choice_index).color);
    window->set_cursor_x_position(initial_c_o_cursor_x_pos);
    window->modify_cursor_position(0, 1);
}

void MenuToolChoice::render_hovered() const
{
    uint16_t initial_c_o_cursor_x_pos = 
        window->get_cursor_position().first;
    
    window->add_ch(' ');
    window->add_ch('>', cursor_color);
    window->add_ch(' ');
    window->add_str(name);
    window->add_str(": ");
    window->add_str(choices.at(choice_index).content, 
        choices.at(choice_index).color);
    window->set_cursor_x_position(initial_c_o_cursor_x_pos);
    window->modify_cursor_position(0, 1);

}

void MenuToolChoice::render_selected() const
{
    uint16_t initial_c_o_cursor_x_pos = 
        window->get_cursor_position().first;
    
    window->modify_cursor_position(3, 0);
    window->add_str(name);
    window->add_ch(':');
    window->set_cursor_x_position(initial_c_o_cursor_x_pos);
    window->modify_cursor_position(0, 1);

    if(choices.size() == 0) return;

    for(int i = 0; i < cursor_index; ++i)
    {
        window->modify_cursor_position(6, 0);

        window->add_str(choices.at(i).content,
            choices.at(i).color);

        window->set_cursor_x_position(initial_c_o_cursor_x_pos);
        window->modify_cursor_position(0, 1);
    }

    window->modify_cursor_position(4, 0);
    window->add_ch('>', cursor_color);
    window->add_ch(' ');

    window->add_str(choices.at(cursor_index).content,
        choices.at(cursor_index).color);

    window->set_cursor_x_position(initial_c_o_cursor_x_pos);
    window->modify_cursor_position(0, 1);

    for(int i = cursor_index + 1; i < choices.size(); ++i)
    {
        window->modify_cursor_position(6, 0);

        window->add_str(choices.at(i).content,
            choices.at(i).color);

        window->set_cursor_x_position(initial_c_o_cursor_x_pos);
        window->modify_cursor_position(0, 1);
    }
}

std::string MenuToolChoice::get_choice() 
    { return choices.at(choice_index).content; }

MenuToolItem::Status MenuToolChoice::handle_input() 
{
    const std::vector<uint32_t> keys = 
        input_handler->get_all_pressed_and_available_keys();

    for(uint32_t key : keys)
    {
        switch(key)
        {
            case SDLK_RETURN:

                input_handler->block_key_until_released(SDLK_RETURN);
                choice_index = cursor_index;
                return HOVERED;

            case SDLK_w:    

                input_handler->set_delay(SDLK_w, 10);

                if(input_handler->is_key_pressed(SDLK_LSHIFT) || 
                    input_handler->is_key_pressed(SDLK_RSHIFT))
                {
                    cursor_index = 0;
                    return SELECTED;
                }

                if(cursor_index > 0) --cursor_index;

                return SELECTED;

            case SDLK_s:

                input_handler->set_delay(SDLK_s, 10);

                if(input_handler->is_key_pressed(SDLK_LSHIFT) || 
                    input_handler->is_key_pressed(SDLK_RSHIFT))
                {
                    cursor_index = choices.size() - 1;
                    return SELECTED;
                }

                if(cursor_index < choices.size() - 1) ++cursor_index;

                return SELECTED;

            case SDLK_f:    

                input_handler->block_key_until_released(SDLK_f);
                return HOVERED;
        }
    }

    return SELECTED;
}
