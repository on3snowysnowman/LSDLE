#pragma once

#include <queue>
#include <string>
#include <unordered_map> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#include "TextureHandler.h"


/**
 * @brief Handles the drawing of characters to the screen each frame. 
 * 
 * @attention Text is added to a queue, and popped off when rendered each
 * frame. Text must be re-added for each frame it should continuosly be on the
 * screen, and the clear function should only be called when the text in the 
 * buffer MUST be emptied before the next frame render.
 * 
 */
class TextDisplayHandler
{

public:

    TextDisplayHandler();

    /**
     * @brief Queues a character to be rendered at a position (in pixels) on
     * the next render call.
     * 
     * @param character Character to render
     * @param x_pos X position in pixels
     * @param y_pos Y position in pixels
     */
    void add_ch(char character, int x_pos, int y_pos);

    /**
     * @brief Queues a character to be rendered at a position (in pixels) on
     * the next render call. Applies a color to the character.
     * 
     * @param character Character to render
     * @param x_pos X position in pixels
     * @param y_pos Y position in pixels
     * @param color Name of the color
     */
    void add_ch(char character, int x_pos, int y_pos, 
        std::string color);

    /**
     * @brief Queues a string to be rendered at a position (in pixels) on
     * the next render call.
     * 
     * @attention Note that the full string may go out of bounds of the screen
     * if added too close to the edge. This function does not handle text 
     * wrapping, that functionality is up to the user.
     * 
     * @param str String to render
     * @param x_pos X position in pixels
     * @param y_pos Y position in pixels
     */
    void add_str(std::string str, int x_pos, int y_pos);

    /**
     * @brief Queues a string to be rendered at a position (in pixels) on
     * the next render call.
     * 
     * @attention Note that the full string may go out of bounds of the screen
     * if added too close to the edge. This function does not handle text 
     * wrapping, that functionality is up to the user.
     * 
     * @param str String to render
     * @param x_pos X position in pixels
     * @param y_pos Y position in pixels
     */
    void add_str(std::string str, int x_pos, int y_pos, std::string   
        color);

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
     * @brief Renders queued characters to the screen.
     */
    void render();

    /**
     * @brief Returns the source font width, with no regard to the current
     * font size multiplier.
     */
    uint8_t get_raw_font_width();

    /**
     * @brief Returns the source font height, with no regard to the current
     * font size multiplier.
     */
    uint8_t get_raw_font_height();

    /**
     * @brief Returns the font width multiplied by the font size multiplier.
     */
    uint8_t get_scaled_font_width();

    /**
     * @brief Returns the font height multiplied by the font size multiplier.
     */
    uint8_t get_scaled_font_height();

private:

    /**
     * @brief Contains data for a character that will be rendered on the next
     * render call. 
     * 
     * This data includes the character symbol itself and its position to be
     * rendered on the screen
     */
    class QueuedRenderedCharacter
    {

    public:

        QueuedRenderedCharacter();

        QueuedRenderedCharacter(char _symbol, SDL_Rect& _destination,
            std::string _color = "");

        // If this character is colored
        bool colored = false;
        
        // ASCII Symbol this character represents
        char symbol = ' ';

        // Destination dimensions for drawing on the screen
        SDL_Rect destination;

        // Color of this character, if any
        std::string color;

    };

    /**
     * @brief Underlying method for rendering chars to the screen. 
     * 
     * Takes an optional parameter for a color. If color is not empty, 
     * the color will be applied to the character. 
     * 
     * @param character Character to render
     * @param x_pos X position
     * @param y_pos Y position
     * @param color Name of the color, if any
     */
    void _add_ch(char character, int x_pos, int y_pos, std::string 
        color = "");

    /**
     * @brief Underlying method for rendering strings to the screen
     * 
     * Takes an optional parameter for a color. If color is not empty,
     * the color will be applied to the string
     * 
     * @param str String to render
     * @param x_pos X position
     * @param y_pos Y position
     * @param color Name of the color, if any
     */
    void _add_str(std::string str, int x_pos, int y_pos, std::string 
        color = "");

    /**
     * @brief Returns initial_size scaled by the font_size_multiplier
     * 
     * @note This method uses std::ceil on the operation, so any float is 
     * rounded up.
     * 
     * @param intial_size Integer to scale
     */
    int get_scaled_size_value(int intial_size);

    // Path to the font data file
    std::string font_path = "logs_font_data.json";

    uint8_t font_width; // Width of each character in pixels
    uint8_t font_height; // Width of each character in height

    /**
     * Multiplier the final character size will be multiplier by
     */
    float font_size_multiplier = 2.0; 

    SDL_Texture* font_texture;

    // Characters that are queued to render on the next render call
    std::queue<QueuedRenderedCharacter> queued_characters;

    // Positions of each char in the font png file
    std::unordered_map<char, std::pair<uint8_t, uint8_t>> 
        char_source_positions;

    TextureHandler* texture_handler = nullptr;
};