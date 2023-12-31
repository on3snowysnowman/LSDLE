#include "MenuTools.h"

#include <iostream>


// Constructors / Deconstructor

MenuTools::MenuTools() {}

MenuTools::MenuTools(ConsoleOutputHandler* _console_output_handler,
    InputHandler* _input_handler)
{
    console_output_handler = _console_output_handler;
    input_handler = _input_handler;
}


// Public

void MenuTools::simulate_list_selection(
    ListSelectionDataContainer& l_s_d_c)
{
    handle_list_selection_input(l_s_d_c);
    render_list_selection(l_s_d_c);
}

void MenuTools::simulate_menu(MenuSimulationDataContainer& m_s_d_c)
{
    handle_menu_simulation_input(m_s_d_c);
    render_menu_simulation(m_s_d_c);
}


// Private

void MenuTools::render_list_selection(ListSelectionDataContainer& 
    l_s_d_c)
{
    if(l_s_d_c.content.size() == 0) return;

    uint16_t start_c_o_handler_cursor_x_pos = 
        console_output_handler->get_cursor_position().first;

    for(int i = 0; i < l_s_d_c.cursor_pos; ++i)
    {
        console_output_handler->add_str("   ");
        console_output_handler->add_str(l_s_d_c.content.at(i).content, 
            l_s_d_c.content.at(i).color);
        console_output_handler->move_cursor_x(start_c_o_handler_cursor_x_pos);
        console_output_handler->modify_cursor_position(0, 1);
    }

    console_output_handler->add_ch(' ');
    console_output_handler->add_ch('>', l_s_d_c.cursor_color);
    console_output_handler->add_ch(' ');
    console_output_handler->add_str(l_s_d_c.content.at(l_s_d_c.cursor_pos).content,
        l_s_d_c.content.at(l_s_d_c.cursor_pos).color);
    console_output_handler->move_cursor_x(start_c_o_handler_cursor_x_pos);
    console_output_handler->modify_cursor_position(0, 1);
    
    for(int i = l_s_d_c.cursor_pos + 1; i < l_s_d_c.content.size(); ++i)
    {
        console_output_handler->add_str("   ");
        console_output_handler->add_str(l_s_d_c.content.at(i).content, 
            l_s_d_c.content.at(i).color);
        console_output_handler->move_cursor_x(start_c_o_handler_cursor_x_pos);
        console_output_handler->modify_cursor_position(0, 1);
    }
}

void MenuTools::handle_list_selection_input(ListSelectionDataContainer&
    l_s_d_c)
{
    std::vector<uint32_t> keys = input_handler->
        get_all_pressed_and_available_keys();

    bool shift_pressed = input_handler->is_key_pressed(SDLK_LSHIFT) || 
        input_handler->is_key_pressed(SDLK_RSHIFT);

    for(uint8_t k : keys)
    {
        switch(k)
        {
            case SDLK_RETURN:

                if(l_s_d_c.block_enter_key) 
                {
                    input_handler->block_key_until_released(SDLK_RETURN);
                }

                else
                {
                    input_handler->set_delay(SDLK_RETURN);
                }

                l_s_d_c.item_has_been_selected = true;
                return;       

            case SDLK_w:

                input_handler->set_delay(k, 10);

                if(shift_pressed)
                {
                    l_s_d_c.cursor_pos = 0;
                    return;
                }

                if(l_s_d_c.cursor_pos - 1 >= 0)
                {
                    --l_s_d_c.cursor_pos;
                }

                return;
            
            case SDLK_s:

                input_handler->set_delay(k, 10);

                if(shift_pressed)
                {
                    l_s_d_c.cursor_pos = l_s_d_c.content.size() - 1;
                    return;
                }

                if(l_s_d_c.cursor_pos + 1 < l_s_d_c.content.size())
                {
                    ++l_s_d_c.cursor_pos;
                }

                return;
        }
    }
}

void MenuTools::render_menu_simulation(MenuSimulationDataContainer& 
    m_s_d_c)
{
    // There is an item selected
    if(m_s_d_c.selected_pos > -1)
    {   
        // Iterate through the MenuToolItems before the selected item
        for(int i = 0; i < m_s_d_c.selected_pos; ++i)
        {
            // Render the item with a no status render
            m_s_d_c.content.at(i)->render_no_status();
        }

        // Render the selected item with a selected render
        m_s_d_c.content.at(m_s_d_c.selected_pos)->render_selected();

        // Iterate through the MenuToolItems after the selected item
        for(int i = m_s_d_c.selected_pos + 1; i < m_s_d_c.content.size(); 
            ++i)
        {
            // Render the item with a no status render
            m_s_d_c.content.at(i)->render_no_status();
        }
    }

    // There is no item selected
    else
    {
        // Iterate through the MenuToolItems before the hovered item
        for(int i = 0; i < m_s_d_c.cursor_pos; ++i)
        {  
            // Render the item with a no status render
            m_s_d_c.content.at(i)->render_no_status();
        }

        // Render the hovered item with a hovered render
        m_s_d_c.content.at(m_s_d_c.cursor_pos)->render_hovered();

        // Iterate through the MenuToolItems after the hovered item
        for(int i = m_s_d_c.cursor_pos + 1; i < m_s_d_c.content.size(); 
            ++i)
        {
            // Render the item with a no status render
            m_s_d_c.content.at(i)->render_no_status();
        }
    }
}

void MenuTools::handle_menu_simulation_input(MenuSimulationDataContainer&
    m_s_d_c) 
{
    // There is an item selected
    if(m_s_d_c.selected_pos > -1)
    {   
        // Signal the selected item to handle the user's input. If the return 
        // status of the item is HOVERED, deselect this item
        if(m_s_d_c.content.at(m_s_d_c.selected_pos)->handle_input() == 
            MenuToolItem::HOVERED)
        {
            m_s_d_c.selected_pos = -1;
            return;
        }

    }

    // No item is selected
    else
    {   
        std::vector<uint32_t> keys = input_handler->
            get_all_pressed_and_available_keys();

        for(uint32_t key : keys)
        {
            switch(key)
            {
                // Select an item
                case SDLK_RETURN:

                    input_handler->block_key_until_released(SDLK_RETURN);

                    m_s_d_c.selected_pos = m_s_d_c.cursor_pos;

                    return;;
                
                // Move the cursor down
                case SDLK_w:

                    input_handler->set_delay(SDLK_w);

                    // If the shift key is pressed
                    if(input_handler->is_key_pressed(SDLK_LSHIFT) || 
                        input_handler->is_key_pressed(SDLK_RSHIFT))
                    {
                        // Jump to the beginning of the list
                        m_s_d_c.cursor_pos = 0;
                        return;
                    }

                    // The shift key isn't pressed, so instead of jumping to
                    // the top of the list, try to move the cursor up a single
                    // position

                    // If the cursor is not at the very bottom of the list
                    if(m_s_d_c.cursor_pos > 0)
                    {
                        // Move the cursor up a position
                        --m_s_d_c.cursor_pos;
                        return;
                    }
                    
                    return;;

                // Move the cursor up
                case SDLK_s:

                    input_handler->set_delay(SDLK_s);

                    // If the shift key is pressed 
                    if(input_handler->is_key_pressed(SDLK_LSHIFT) || 
                        input_handler->is_key_pressed(SDLK_RSHIFT))
                    {
                        // Jump to the end of the list 
                        m_s_d_c.cursor_pos = m_s_d_c.content.size() - 1;
                        return;
                    }

                    // The shift key isn't pressed, so instead of jumping to
                    // the top of the list, try to move the cursor down a 
                    // single position

                    // If the cursor is not at the very end of the list
                    if(m_s_d_c.cursor_pos < m_s_d_c.content.size() - 1)
                    {
                        // Move the cursor down a position
                        ++m_s_d_c.cursor_pos;
                        return;
                    }

                    return;;
                
            }
        }
    }
}
