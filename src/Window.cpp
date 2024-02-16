#include "LSDLE.h"
#include "Window.h"

// Constructors / Deconstructor

Window::Window(uint16_t _start_x, uint16_t _start_y, uint16_t _end_x, 
    uint16_t _end_y) 
{   
    // Add this window to the WindowManager

    WindowManager::add_window(this);

    texture_handler = LSDLE::get_texture_handler();

    sprite_handler = new SpriteHandler();

    console_output_handler = new ConsoleOutputHandler(_start_x + border_size, 
        _start_y + border_size, _end_x - border_size, _end_y - border_size);

    text_display_handler = console_output_handler->get_text_display_handler();

    resize_window(_start_x, _start_y, _end_x, _end_y);
}

// Public

void Window::render()
{
    console_output_handler->render();
    sprite_handler->render();
}

void Window::resize_window(uint16_t _start_x, uint16_t _start_y,
    uint16_t _end_x, uint16_t _end_y)
{
    start_x = _start_x;
    start_y = _start_y;
    end_x = _end_x;
    end_y = _end_y;
}

void Window::reset_cursor_position() 
{ console_output_handler->reset_cursor_position(); }

void Window::reset_anchor() { console_output_handler->set_anchor(0); }

void Window::modify_cursor_position(uint16_t delta_x, uint16_t delta_y) 
{
    console_output_handler->modify_cursor_position(delta_x, delta_y);
}

void Window::set_cursor_x_position(uint16_t x) 
{
    console_output_handler->move_cursor_x(x);
}

void Window::set_cursor_y_position(uint16_t y) 
{
    console_output_handler->move_cursor_y(y);
}

void Window::set_cursor_position(uint16_t x, uint16_t y) 
{
    console_output_handler->move_cursor(x, y);
}

void Window::set_anchor(uint16_t _anchor)
{
    console_output_handler->set_anchor(_anchor);
}

void Window::add_new_line(uint8_t num_new_line)
{
    console_output_handler->add_new_line(num_new_line);
}

void Window::add_ch(char c) 
{
    console_output_handler->add_ch(c);
}

void Window::add_ch(char c, std::string color) 
{
    console_output_handler->add_ch(c, color);
}

void Window::add_char_at_pixel_position(char c, uint16_t x, uint16_t y) 
{
    text_display_handler->add_ch(c, x, y);
}

void Window::add_char_at_pixel_position(char c, uint16_t x, uint16_t y, 
    std::string color) 
{
    text_display_handler->add_ch(c, x, y, color);
}

void Window::add_str(std::string str) 
{
    console_output_handler->add_str(str);
}

void Window::add_str(std::string str, std::string color) 
{
    console_output_handler->add_str(str, color);
}

void Window::add_str_at_pixel_position(std::string str, 
    uint16_t x, uint16_t y) 
{
    text_display_handler->add_str(str, x, y);
}

void Window::add_str_at_pixel_position(std::string str, uint16_t x, uint16_t y,
    std::string color) 
{
    text_display_handler->add_str(str, x, y, color);
}

void Window::add_sprite_at_cursor_pos(Sprite* s)
{
    std::pair<uint16_t, uint16_t> cursor_pos_in_pixels = 
        console_output_handler->get_cursor_position_in_pixels();
        
    sprite_handler->render_sprite(s, cursor_pos_in_pixels.first + 
    border_size, cursor_pos_in_pixels.second + border_size);
}

const std::pair<uint16_t, uint16_t>& Window::get_cursor_position() 
    { return console_output_handler->get_cursor_position(); }

// Private


// ----------------------------- WINDOW_MANAGER ---------------------------- //

// Static Members

std::vector<Window*> WindowManager::windows;

// Public

void WindowManager::update()
{
    for(Window* w : windows)
    {
        w->render();
    }
}

void WindowManager::add_window(Window* w)
{
    windows.push_back(w);
}
