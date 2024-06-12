#pragma once

#include <string>
#include <functional>

#include "MenuToolItem.h"
#include "ConsoleOutputHandler.h"
#include "InputHandler.h"
#include "SimulationDataContainers.h"
#include "Window.h"


template<typename T>
class MenuToolButton : public MenuToolItem
{

public:

    MenuToolButton() = delete;

    MenuToolButton(T* _object_ptr, std::function<void(T&)> 
        _callback_function, Window* window, std::string _name, 
        std::string _cursor_color, std::string _button_color) : MenuToolItem(window, _cursor_color, BUTTON)
    {
        name = _name;
        button_color = _button_color;
        object_ptr = _object_ptr;
        callback_function = _callback_function;
    }

    void render_no_status() const final
    {
        uint16_t initial_c_o_cursor_x_pos = 
        window->get_cursor_position().first;

        window->modify_cursor_position(3, 0);
        // window->add_ch('[');
        window->add_str(name, button_color);
        // window->add_ch(']');
        window->set_cursor_x_position(
            initial_c_o_cursor_x_pos);
        window->modify_cursor_position(0, 1);
    }

    void render_hovered() const final
    {
        uint16_t initial_c_o_cursor_x_pos = 
        window->get_cursor_position().first;

        window->add_ch(' ');
        window->add_ch('>', cursor_color);
        window->add_ch(' ');
        // window->add_ch('[');
        window->add_str(name, button_color);
        // window->add_ch(']');
        window->set_cursor_x_position(
            initial_c_o_cursor_x_pos);
        window->modify_cursor_position(0, 1);
    }

    void render_selected() const final
    {
        uint16_t initial_c_o_cursor_x_pos = 
        window->get_cursor_position().first;

        window->add_ch(' ');
        window->add_ch('>', cursor_color);
        window->add_ch(' ');
        // window->add_ch('[');
        window->add_str(name, button_color);
        // window->add_ch(']');
        window->set_cursor_x_position(
            initial_c_o_cursor_x_pos);
        window->modify_cursor_position(0, 1);
    }

    Status handle_input() final
    {
        // Trigger the callback function
        callback_function(*object_ptr);

        return HOVERED;
    }


private:

    std::string name;
    std::string button_color;

    T* object_ptr;
    std::function<void(T&)> callback_function;

};
