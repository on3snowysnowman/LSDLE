#pragma once

#include <cstdint>
#include <string>

#include "TextDisplayHandler.h"
#include "TextureHandler.h"

/**
 * @brief Outputs text to the screen like a Console would.
 * 
 * The ConsoleOutputHandler has a 'cursor' that will move right across the
 * screen as characters are added. The cursor can be moved using the 
 * move_cursor() method. This class contains support for text wrapping, 
 * so the cursor does not need to be manually placed on the next line. If 
 * a new line is desired, use the new_line method. This class uses the 
 * TextDisplayHandler which clears content as it is rendered, so there is no
 * need to call the clear_buffer() method if the intent is to refresh / clear
 * the screen between each render call. This is done automatically.
 * 
 * @attention The cursor's position is measured in characters, not in pixels as
 * the TextDisplayHandler does. This applies to the move_cursor method too. If
 * the cursor needs to be moved 6 characters to the right, simply add 6 to the
 * cursor's current position. Although the cursor's position is in characters,
 * the constructor's start and end parameters are pixel dimensions.
 */
class ConsoleOutputHandler
{

public:

    ConsoleOutputHandler();

    ConsoleOutputHandler(uint16_t _start_x, uint16_t _start_y, 
        uint16_t _end_x, uint16_t _end_y);

    /**
     * @brief Moves the cursor to a position on the screen.
     * 
     * @attention The x and y positions are measure in characters, not
     * in pixels.
     * 
     * @param x X position
     * @param y Y position
     */
    void move_cursor(uint16_t x, uint16_t y);

    /**
     * @brief Moves the cursor's x position to a new position.
     * 
     * @param x X position
     */
    void move_cursor_x(uint16_t x);

    /**
     * @brief Moves the cursor's y position to a new position.
     * 
     * @param y Y position
     */
    void move_cursor_y(uint16_t y);

    /**
     * @brief Modifies the cursor's x and y position by the passed amount.
     * 
     * Positive values will increment the cursor's position, while negative
     * values will decrement.
     * 
     * @param x_modify Amount to modify x by
     * @param y_modify Amount to modify y by
     */
    void modify_cursor_position(uint16_t x_modify, uint16_t y_modify);

    /**
     * @brief Adds a character to the screen.
     * 
     * @param c Character to add
     */
    void add_ch(char c);

    /**
     * @brief Adds a character to the screen. Applies a color to the
     * character.
     * 
     * @param c Character to add
     * @param color Color to apply
     */
    void add_ch(char c, std::string color);

    /**
     * @brief Adds a string to the screen. Supports text wrapping, so 
     * characters that would go off screen will move to the next line.
     * 
     * @param str String to add
     */
    void add_str(std::string str);

    /**
     * @brief Adds a string to the screen. Supports text wrapping, so
     * characters that would go off screen will move to the next line. 
     * Applies a color to the string.
     * 
     * @param str String to add
     * @param color Color to apply
     */
    void add_str(std::string str, std::string color);

    /**
     * @brief Adds a new line, moving the cursor down num amount of times
     * 
     * @param num Amount of new lines
     */
    void add_new_line(uint8_t num = 1);

    /**
     * @brief Clears the queued character buffer.
     * 
     * @attention Only use this method if the intent is to clear the buffer 
     * before the characters added this frame can be rendered. Do not use this 
     * function to 'clear' the screen each frame, as text will automatically 
     * clear per each render call.
     */
    void clear_buffer();

    /**
     * @brief Resets the cursor's position to the top left of the screen.
     */
    void reset_cursor_position();

    /**
     * @brief Renders buffered content to the screen. The cursor's position
     * is also reset to the top left of the screen.
     */
    void render(); 

    /**
     * @brief Sets the "anchor" to a new position. 
     * 
     * The anchor is the x position on the screen that the cursor will be 
     * set to when a new line is added.
     * 
     * @param _anchor 
     */
    void set_anchor(uint16_t _anchor);

    std::pair<uint16_t, uint16_t> get_cursor_position_in_pixels();

    /**
     * @brief Returns the cursor's position.
     * 
     * @attention The cursor's position is measure in characters, not in 
     * pixels.
     */
    const std::pair<uint16_t, uint16_t>& get_cursor_position() const;

    TextDisplayHandler* get_text_display_handler();

private:
    
    void _add_ch(char c, std::string color = "");

    void _add_str(std::string str, std::string color = "");

    // Starting X position of the screen
    uint16_t start_x {};

    // Ending X position of the screen
    uint16_t end_x {};

    // Starting Y position of the screen
    uint16_t start_y {};

    // Ending Y position of the screen
    uint16_t end_y {};
    
    // Width of the screen, measured in characters rounded down
    uint16_t screen_character_width = 0;

    // Height of the screen, measure in characters rounded down
    uint16_t screen_character_height = 0;

    /**
     * Width of the font, scaled with the TextDisplayHandler's font size
     * multiplier
     */
    uint16_t font_width {};

    /**
     * Height of the font, scaled with the TextDisplayHandler's font size
     * multiplier
     */
    uint16_t font_height {};

    // The x position that a new line will "anchor" to when placing a new line
    uint16_t anchor {}; 

    /**
     * Size multiplier that the space between the characters vertical wise will
     * be multiplied by. This enhances readability with multiple lines of 
     * characters.
     */
    static const float VERTICAL_SPACE_MODIFIER;

    // Cursor's position, measured in characters
    std::pair<uint16_t, uint16_t> cursor_position {0, 0};

    TextDisplayHandler text_display_handler;

};