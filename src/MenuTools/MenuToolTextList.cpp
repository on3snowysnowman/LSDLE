#include "MenuToolTextList.h"

#include <iostream>

// Constructors / Deconstructor

MenuToolTextList::MenuToolTextList() 
:
MenuToolItem() {}

MenuToolTextList::MenuToolTextList(Window* _window, std::string _cursor_color, std::string _name,
    uint16_t _cursor_pos, int32_t _selected_pos) :
    MenuToolItem(_window, _cursor_color, TEXT_LIST) 
{
    name = _name;
    cursor_pos = _cursor_pos;
    selected_pos = _selected_pos;
}


// Public


void MenuToolTextList::reset()
{
    cursor_pos = 0;
}

void MenuToolTextList::render_no_status() const
{
    uint16_t initial_c_o_cursor_x_pos = 
        window->get_cursor_position().first;

    window->modify_cursor_position(3, 0);
    window->add_str(name + ':');
    window->set_cursor_x_position(initial_c_o_cursor_x_pos);
    window->modify_cursor_position(3, 1);

    for(const MenuToolText& text : content)
    {
        text.render_no_status();
    }

    window->add_str("   [Add Text]");

    window->set_cursor_x_position(initial_c_o_cursor_x_pos);
    window->modify_cursor_position(0, 1);
}

void MenuToolTextList::render_hovered() const
{
    uint16_t initial_c_o_cursor_x_pos = 
        window->get_cursor_position().first;

    window->add_str(" > ", cursor_color);
    window->add_str(name + ':');
    window->set_cursor_x_position(initial_c_o_cursor_x_pos);
    window->modify_cursor_position(3, 1);

    for(const MenuToolText& text : content)
    {
        text.render_no_status();
    }

    window->add_str("   [Add Text]");

    window->set_cursor_x_position(initial_c_o_cursor_x_pos);
    window->modify_cursor_position(0, 1);
}

void MenuToolTextList::render_selected() const
{
    uint16_t initial_c_o_cursor_x_pos = 
        window->get_cursor_position().first;
    
    window->modify_cursor_position(3, 0);
    window->add_str(name + ':');

    window->set_cursor_x_position(initial_c_o_cursor_x_pos);
    window->modify_cursor_position(3, 1);

    // An item is selected
    if(selected_pos > -1)
    {
        // If the Add Text button is selected
        if(selected_pos == content.size())
        {
            for(const MenuToolText& text : content)
            {
                text.render_no_status();
            }

            window->add_str(" > ", cursor_color);
            window->add_str("[Add Text]");
        }

        // A MenuToolText item is selected
        else
        {
            for(int i = 0; i < selected_pos; ++i)
            {
                content.at(i).render_no_status();
            }

            content.at(selected_pos).render_selected();

            for(int i = selected_pos + 1; i < content.size(); ++i)
            {
                content.at(i).render_no_status();
            }

            window->add_str("   [Add Text]");
        }
    }

    // No item is selected
    else
    {
        // The Add Text button is hovered
        if(cursor_pos == content.size())
        {
            for(const MenuToolText& text : content)
            {
                text.render_no_status();
            }

            window->add_str(" > ", cursor_color);
            window->add_str("[Add Text]");
        }

        // A MenuToolText item is hovered
        else
        {
            for(int i = 0; i < cursor_pos; ++i)
            {
                content.at(i).render_no_status();
            }

            content.at(cursor_pos).render_hovered();

            for(int i = cursor_pos + 1; i < content.size(); ++i)
            {
                content.at(i).render_no_status();
            }

            window->add_str("   [Add Text]");
        }
    }

    window->set_cursor_x_position(initial_c_o_cursor_x_pos);
    window->modify_cursor_position(0, 1);
}

MenuToolItem::Status MenuToolTextList::handle_input()
{
    // An item is selected
    if(selected_pos > -1)
    {
        // The Add Text button is selected
        if(selected_pos == content.size())
        {
            content.insert(content.begin() + content.size(), MenuToolText(
                    window, cursor_color, "Text"));

            ++cursor_pos;
            selected_pos = -1;
            return SELECTED;
        }

        // A MenuToolText item is selected

        if(content.at(selected_pos).handle_input() == HOVERED)
        {
            if(content.at(cursor_pos).content.size() == 0)
            {
                content.erase(content.begin() + cursor_pos);
                
                if(cursor_pos != 0) --cursor_pos;
            }

            selected_pos = -1;
        }

        return SELECTED;
    }

    // No item is selected

    std::vector<uint32_t> keys = input_handler->
        get_all_pressed_and_available_keys();

    for(uint32_t key : keys)
    {
        switch(key)
        {
            case SDLK_BACKSPACE:

                input_handler->block_key_until_released(SDLK_BACKSPACE);

                // The Add Text button is selected, which shouuld not be deleted
                if(cursor_pos == content.size()) return SELECTED;

                content.erase(content.begin() + cursor_pos);

                if(cursor_pos != 0) --cursor_pos;

                return SELECTED;
            
            case SDLK_RETURN:
                
                input_handler->block_key_until_released(SDLK_RETURN);

                selected_pos = cursor_pos;
                return SELECTED;

            // Move the cursor down
            case SDLK_w:

                input_handler->set_delay(SDLK_w);

                // If the shift key is pressed
                if(input_handler->is_key_pressed(SDLK_LSHIFT) || 
                    input_handler->is_key_pressed(SDLK_RSHIFT))
                {
                    // Jump to the beginning of the list
                    cursor_pos = 0;
                    return SELECTED;
                }

                // The shift key isn't pressed, so instead of jumping to
                // the top of the list, try to move the cursor up a single
                // position

                // If the cursor is not at the very bottom of the list
                if(cursor_pos > 0)
                {
                    // Move the cursor up a position
                    --cursor_pos;
                    return SELECTED;
                }
                
                break;

            // Move the cursor up
            case SDLK_s:

                input_handler->set_delay(SDLK_s);

                // If the shift key is pressed 
                if(input_handler->is_key_pressed(SDLK_LSHIFT) || 
                    input_handler->is_key_pressed(SDLK_RSHIFT))
                {
                    // Jump to the end of the list 
                    cursor_pos = content.size();
                    return SELECTED;
                }

                // The shift key isn't pressed, so instead of jumping to
                // the top of the list, try to move the cursor down a 
                // single position

                // If the cursor is not at the very end of the list
                if(cursor_pos < content.size())
                {
                    // Move the cursor down a position
                    ++cursor_pos;
                    return SELECTED;
                }

                return SELECTED;

            // Deselect the list
            case SDLK_f:

                input_handler->block_key_until_released(SDLK_f);
                return HOVERED;
        }
    }

    return SELECTED;
}


// Private
