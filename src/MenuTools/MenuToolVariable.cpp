#include "Debug.h"
#include "MenuToolVariable.h"
#include "LNumericLimits.h"

#include <iostream>


// Constructors / Deconstructor

MenuToolVariable::MenuToolVariable() {}

MenuToolVariable::MenuToolVariable(Window* _window, 
    MenuToolItem::StringType _str_type, std::string _cursor_color, 
    std::string _name, std::string _content) : 
    MenuToolItem(_window, _cursor_color,
    VARIABLE)
{
    str_type = _str_type;
    name = _name;
    content = _content;

    // If the type of this Variable is a float
    if(str_type == StringType::FLOAT)
    {
        // Set the input handling function to the FLOAT one
        targ_input_handling_function = &MenuToolVariable::handle_float_input;

        if(content.size() == 0) 
        {
            content.push_back('0');
            return;
        }

        // Validate the content parameter by checking if it is filled with only
        // numbers, and there is at most 1 decimal point.

        // Iterate through each char
        for(char c : content)
        {
            // If the char is a decimal point
            if(c == '.')
            {
                // If a decimal point has already been found in the content
                if(has_decimal_point)
                {
                    // Throw an error, since there can't be a float with two 
                    // decimal points
                    std::string message = "MenuToolVariable.MenuToolVariable"
                        "(ConsoleOutputHandler* _window, "
                        "InputHandler* _input_handler, MenuToolItem::"
                        "StringType _str_type, std::string _cursor_color, "
                        "std::string _name, std::string _content) -> Attempted"
                        " to create a Variable of Float type with two "
                        "decimal points";

                    Debug::log(message, Debug::ERR);
                    exit(0);
                }
            }

            // If the char is not a number
            else if(c < 48 || c > 57)
            {
                // Throw an error, since there can't be a float with letters
                std::string message = "MenuToolVariable.MenuToolVariable"
                    "(ConsoleOutputHandler* _window, "
                    "InputHandler* _input_handler, MenuToolItem::"
                    "StringType _str_type, std::string _cursor_color, "
                    "std::string _name, std::string _content) -> Attempted"
                    " to create a Variable of Float type with alphabetical "
                    "characters.";

                Debug::log(message, Debug::ERR);
                exit(0);
            }
        }
    }

    // If the type of the Variable is an int
    else if(str_type == StringType::INT)
    {
        // Set the input handling function to the INT one.
        targ_input_handling_function = &MenuToolVariable::handle_int_input;

        if(content.size() == 0)
        {
            content.push_back('0');
            
            return;
        }

        // Validate the content parameter by checking if it is filled with only
        // numbers.

        // Iterate through each char
        for(char c : content)
        {
            if(c == '.')
            {
                // Throw an error, since an int can't have a decimal point
                std::string message = "MenuToolVariable.MenuToolVariable"
                    "(ConsoleOutputHandler* _window, "
                    "InputHandler* _input_handler, MenuToolItem::"
                    "StringType _str_type, std::string _cursor_color, "
                    "std::string _name, std::string _content) -> Attempted"
                    " to create a Variable of Int type with a decimal "
                    "point";
                
                Debug::log(message, Debug::ERR);
                exit(0);
            }

            // If the char is not a number
            else if(c < 48 || c > 57)
            {
                // Throw an error, since there can't be a float with letters
                std::string message = "MenuToolVariable.MenuToolVariable"
                    "(ConsoleOutputHandler* _window, "
                    "InputHandler* _input_handler, MenuToolItem::"
                    "StringType _str_type, std::string _cursor_color, "
                    "std::string _name, std::string _content) -> Attempted"
                    " to create a Variable of Int type with alphabetical "
                    "characters.";

                Debug::log(message, Debug::ERR);
                exit(0);
            }
        }
    }

    // The type of the Variable is a string

    // No validation needs to be done to the content parameter, since all
    // characters are valid for a STRING type Variable.

    else
    {
        // Set the input handling function to the STRING one.
        targ_input_handling_function = &MenuToolVariable::handle_string_input;
    }

}


// Public

void MenuToolVariable::render_no_status() const
{
    uint16_t initial_c_o_cursor_x_pos = 
        window->get_cursor_position().first;
    
    window->modify_cursor_position(3, 0);
    window->add_str(name);
    window->add_ch(':');
    window->add_str(" " + content);
    window->set_cursor_x_position(initial_c_o_cursor_x_pos);
    window->modify_cursor_position(0, 1);
}

void MenuToolVariable::render_hovered() const
{
    uint16_t initial_c_o_cursor_x_pos = 
        window->get_cursor_position().first;

    window->add_ch(' ');
    window->add_ch('>', cursor_color);
    window->add_ch(' ');
    window->add_str(name);
    window->add_str(": ");
    window->add_str(content);
    window->set_cursor_x_position(initial_c_o_cursor_x_pos);
    window->modify_cursor_position(0, 1);
}

void MenuToolVariable::render_selected() const
{
    uint16_t initial_c_o_cursor_x_pos = 
        window->get_cursor_position().first;

    window->add_str("  ");
    window->add_ch('>', cursor_color);
    window->add_ch(' ');
    window->add_str(name);
    window->add_str(": ");
    window->add_str(content, cursor_color);
    window->add_ch('_');
    window->set_cursor_x_position(initial_c_o_cursor_x_pos);
    window->modify_cursor_position(0, 1);
}

MenuToolItem::Status MenuToolVariable::handle_input()
{
    // Call the respective input handling function. This function pointer is 
    // set during the construction of this object, and changes depending on 
    // type of the Variable.

    MenuToolItem::Status status = (this->*targ_input_handling_function)();

    return status;

    // return (this->*targ_input_handling_function)();
}

uint16_t MenuToolVariable::fetch_int()
{
    uint16_t num {};

    // Attempt to convert the content to an int
    try
    {
        num = std::stoi(content);
        return num;
    }

    // Numeric interpretation of the string was too large
    catch(std::out_of_range)
    {
        Debug::log("MenuToolVariable.fetch_int() : Attempted conversion of "
            "content caused an overflow error", Debug::WARN);

        return LNumericLimits::UINT16_LIMIT;
    }
}

// Private

MenuToolItem::Status MenuToolVariable::handle_float_input()
{
    const std::vector<uint32_t>* KEYS = &input_handler->get_raw_keys();

    // Iterate through each pressed key
    for(uint32_t key : *KEYS)
    {
        switch(key)
        {
            case SDLK_RETURN:

                // If the Float is left empty, emplace a 0 so it still contains 
                // a value
                if(content.size() == 0) content.push_back('0');

                input_handler->block_key_until_released(SDLK_RETURN);
                return HOVERED;
            
            case SDLK_PERIOD:

                // If the content is empty, or if there is already a decimal 
                // point in the content
                if(content.size() == 0 || has_decimal_point) return SELECTED;

                has_decimal_point = true;
                content.push_back('.');
                return SELECTED;
            
            case SDLK_BACKSPACE:

                if(content.size() == 0) return SELECTED;

                // If the shift key is pressed
                if(input_handler->is_key_pressed(SDLK_LCTRL) || 
                    input_handler->is_key_pressed(SDLK_RCTRL))
                {
                    content.clear();
                    has_decimal_point = false;
                    return SELECTED;
                }

                // If the character about to be deleted is the decimal point
                if(content.at(content.size() - 1) == '.') 
                {
                    has_decimal_point = false;
                }

                content.pop_back();

                return SELECTED;
        }

        // The key is a number key
        if(key >= 48 && key <= 57)
        {   
            content.push_back(char(key));
        }
    }

    return SELECTED;
}

MenuToolItem::Status MenuToolVariable::handle_int_input()
{
    const std::vector<uint32_t>* KEYS = &input_handler->get_raw_keys();

    // Iterate through each pressed key
    for(uint32_t key : *KEYS)
    {
        switch(key)
        {
            case SDLK_RETURN:

                if(content.size() == 0) content.push_back('0');

                input_handler->block_key_until_released(SDLK_RETURN);
                return HOVERED;
            
            case SDLK_BACKSPACE:

                if(content.size() == 0) return SELECTED;

                // If the shift key is pressed
                if(input_handler->is_key_pressed(SDLK_LCTRL) || 
                    input_handler->is_key_pressed(SDLK_RCTRL))
                {
                    content.clear();
                    return SELECTED;
                }

                content.pop_back();

                return SELECTED;
        }

        // The key is a number key
        if(key >= 48 && key <= 57)
        {   
            content.push_back(char(key));
        }
    }

    return SELECTED;
}

MenuToolItem::Status MenuToolVariable::handle_string_input()
{
    const std::vector<uint32_t>* KEYS = &input_handler->get_raw_keys();

    for(uint32_t key : *KEYS)
    {
        switch(key)
        {
            case SDLK_RETURN:

                input_handler->block_key_until_released(SDLK_RETURN);
                return HOVERED;
        }

        apply_input_to_string(key, content);
    }

    return SELECTED;
}
