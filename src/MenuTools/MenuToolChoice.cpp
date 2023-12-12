#include "MenuToolChoice.h"


// Constructors / Deconstructor

MenuToolChoice::MenuToolChoice() : MenuToolItem() {}

MenuToolChoice::MenuToolChoice(ConsoleOutputHandler* _console_output_handler,
    InputHandler* _input_handler, std::string _cursor_color, std::string _name,
    uint8_t _choice_index)
    :
    MenuToolItem(_console_output_handler, _input_handler, _cursor_color,
    CHOICE)
{
    cursor_color = _cursor_color;
    name = _name;
    choice_index = _choice_index;
    cursor_index = choice_index;
}


// Public

void MenuToolChoice::render_no_status() const
{
    uint16_t initial_c_o_cursor_x_pos = 
        console_output_handler->get_cursor_position().first;
    
    console_output_handler->modify_cursor_position(3, 0);
    console_output_handler->add_str(name);
    console_output_handler->add_str(": ");
    console_output_handler->add_str(choices.at(choice_index).content, 
        choices.at(choice_index).color);
    console_output_handler->move_cursor_x(initial_c_o_cursor_x_pos);
    console_output_handler->modify_cursor_position(0, 1);
}

void MenuToolChoice::render_hovered() const
{
    uint16_t initial_c_o_cursor_x_pos = 
        console_output_handler->get_cursor_position().first;
    
    console_output_handler->add_ch(' ');
    console_output_handler->add_ch('>', cursor_color);
    console_output_handler->add_ch(' ');
    console_output_handler->add_str(name);
    console_output_handler->add_str(": ");
    console_output_handler->add_str(choices.at(choice_index).content, 
        choices.at(choice_index).color);
    console_output_handler->move_cursor_x(initial_c_o_cursor_x_pos);
    console_output_handler->modify_cursor_position(0, 1);

}

void MenuToolChoice::render_selected() const
{
    uint16_t initial_c_o_cursor_x_pos = 
        console_output_handler->get_cursor_position().first;
    
    console_output_handler->modify_cursor_position(3, 0);
    console_output_handler->add_str(name);
    console_output_handler->add_ch(':');
    console_output_handler->move_cursor_x(initial_c_o_cursor_x_pos);
    console_output_handler->modify_cursor_position(0, 1);

    if(choices.size() == 0) return;

    for(int i = 0; i < cursor_index; ++i)
    {
        console_output_handler->modify_cursor_position(6, 0);

        console_output_handler->add_str(choices.at(i).content,
            choices.at(i).color);

        console_output_handler->move_cursor_x(initial_c_o_cursor_x_pos);
        console_output_handler->modify_cursor_position(0, 1);
    }

    console_output_handler->modify_cursor_position(4, 0);
    console_output_handler->add_ch('>', cursor_color);
    console_output_handler->add_ch(' ');

    console_output_handler->add_str(choices.at(cursor_index).content,
        choices.at(cursor_index).color);

    console_output_handler->move_cursor_x(initial_c_o_cursor_x_pos);
    console_output_handler->modify_cursor_position(0, 1);

    for(int i = cursor_index + 1; i < choices.size(); ++i)
    {
        console_output_handler->modify_cursor_position(6, 0);

        console_output_handler->add_str(choices.at(i).content,
            choices.at(i).color);

        console_output_handler->move_cursor_x(initial_c_o_cursor_x_pos);
        console_output_handler->modify_cursor_position(0, 1);
    }
}

MenuToolItem::Status MenuToolChoice::handle_input() 
{
    const std::vector<uint32_t>* keys = &input_handler->get_raw_keys();

    for(uint32_t key : *keys)
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

                input_handler->set_delay(SDLK_w, 10);

                if(input_handler->is_key_pressed(SDLK_LSHIFT) || 
                    input_handler->is_key_pressed(SDLK_RSHIFT))
                {
                    cursor_index = choices.size();
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
