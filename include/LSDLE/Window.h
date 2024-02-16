#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "ConsoleOutputHandler.h"
#include "TextureHandler.h"
#include "TextDisplayHandler.h"
#include "SpriteHandler.h"


class Window
{

public:

    Window(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y);

    void render();

    void resize_window(uint16_t start_x, uint16_t start_y, uint16_t end_x, 
        uint16_t end_y);

    void reset_cursor_position();
    void reset_anchor();
    void modify_cursor_position(uint16_t delta_x, uint16_t delta_y);
    void set_cursor_x_position(uint16_t x);
    void set_cursor_y_position(uint16_t y);
    void set_cursor_position(uint16_t x, uint16_t y);
    void set_anchor(uint16_t anchor);

    void add_new_line(uint8_t num_new_line = 1);

    void add_ch(char c);
    void add_ch(char c, std::string color);
    void add_char_at_pixel_position(char c, uint16_t x_pos, uint16_t y_pos);
    void add_char_at_pixel_position(char c, uint16_t x_pos, uint16_t y_pos, 
        std::string color);

    void add_str(std::string str);
    void add_str(std::string str, std::string color);
    void add_str_at_pixel_position(std::string str, uint16_t x, uint16_t y);
    void add_str_at_pixel_position(std::string str, uint16_t x, uint16_t y, 
        std::string color);

    void add_sprite_at_cursor_pos(Sprite* s);

    const std::pair<uint16_t, uint16_t>& get_cursor_position();

private:

    uint16_t start_x = 0;
    uint16_t end_x = 0;
    uint16_t start_y = 0;
    uint16_t end_y = 0;

    uint16_t border_size = 10;

    TextureHandler* texture_handler {};
    TextDisplayHandler* text_display_handler {};
    SpriteHandler* sprite_handler {};
    ConsoleOutputHandler* console_output_handler {};
};

class WindowManager
{

public:

    static void update();

    static void add_window(Window* w);

private:

    static std::vector<Window*> windows;

};
