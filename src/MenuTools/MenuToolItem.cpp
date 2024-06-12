#include "MenuToolItem.h"
#include "MenuToolItemType.h"
#include "LSDLE.h"


// Static Members


/**
 * Keys to their respective keys when used with the Shift Key
 */
const std::unordered_map<char, char> MenuToolItem::KEYS_TO_SHIFTED_KEYS
{
    {'\'', '"'},
    {',', '<'},
    {'-', '_'},
    {'.', '>'},
    {'/', '?'},
    {';', ':'},
    {'=', '+'},
    {'[', '{'},
    {'\\', '|'},
    {']', '}'},
    {'0', ')'},
    {'1', '!'},
    {'2', '@'},
    {'3', '#'},
    {'4', '$'},
    {'5', '%'},
    {'6', '^'},
    {'7', '&'},
    {'8', '*'},
    {'9', '('},
};


// Constructors / Deconstructor

MenuToolItem::MenuToolItem() {}

MenuToolItem::MenuToolItem(Window* _window, std::string _cursor_color, 
    MenuToolItemType _item_type)
{
    window = _window;
    input_handler = LSDLE::get_input_handler();

    cursor_color = _cursor_color;

    item_type = _item_type;
}


// Public

void MenuToolItem::start() {}

void MenuToolItem::reset() {}

void MenuToolItem::render_no_status() const {}

void MenuToolItem::render_hovered() const {}

void MenuToolItem::render_selected() const {}

MenuToolItem::Status MenuToolItem::handle_input() { return NO_STATUS; }

void MenuToolItem::set_cursor_color(std::string color)
{
    cursor_color = color;
}

std::string MenuToolItem::get_cursor_color() const { return cursor_color; }

MenuToolItemType MenuToolItem::get_item_type() const { return item_type; }


// Private

void MenuToolItem::apply_input_to_string(uint32_t key, std::string& str)
{
    // If the shift key is pressed this frame
    bool shift_pressed = input_handler->is_key_pressed(SDLK_LSHIFT) || 
        input_handler->is_key_pressed(SDLK_RSHIFT);

    // If the control key is pressed this frame
    bool ctrl_pressed = input_handler->is_key_pressed(SDLK_LCTRL) || 
        input_handler->is_key_pressed(SDLK_RCTRL);

    if(shift_pressed)
    {
        switch(key)
        {
            case SDLK_BACKSPACE:

                if(str.size() == 0) return;

                if(ctrl_pressed)
                {
                    str.clear();
                    return;
                }

                str.pop_back();
                return;

            case SDLK_SPACE:

                str.push_back(' ');
                return;

            case SDLK_TAB:

                str.append("   ");
                return;
        }

        if(key >= 97 && key <= 122)
        {
            str.push_back(char(key - 32));
            return;
        }

        if(KEYS_TO_SHIFTED_KEYS.find(key) != KEYS_TO_SHIFTED_KEYS.end())
        {
            str.push_back(char(KEYS_TO_SHIFTED_KEYS.at(key)));
            return;
        }
    }

    else
    {
        switch(key)
        {
            case SDLK_BACKSPACE:

                if(str.size() == 0) return;

                if(ctrl_pressed)
                {
                    int i = str.size() - 1;

                    // This logic snip here allows the user to press the 
                    // Ctrl key with the Backspace key to delete the first 
                    // word found to the left of the cursor

                    while(i > 0)
                    {
                        if(str.at(i) == ' ')
                        {
                            while(i > 0)
                            {
                                if(str.at(i) != ' ')
                                {
                                    i++;
                                    goto AFTER_LOOP;
                                }

                                i--;
                            }
                        }

                        i --;
                    }

                    AFTER_LOOP:

                    str = str.substr(0, i);
                    return;
                }
        
                str.pop_back();
                break;

            case SDLK_SPACE:

                str.push_back(' ');
                return;

            case SDLK_TAB:

                str.append("   ");
                return;
        }

        // If the key is an alphabetical letter
        if(key >= 33 && key <= 126)
        {
            str.push_back(char(key));
            return;
        }
    }
}