#pragma once

#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <cstdint>
#include <unordered_set>
#include <queue>

#include "TextureHandler.h"

/**
 * @brief Contains data for rendering png sprites to the screen.
 * 
 * The source parameters define the position, and dimensions that
 * will be spliced from the png image at the path. The dimension parameters 
 * resemble the position and dimensions that will be rendered on the screen.
 */
class Sprite
{

public:

    Sprite();

    bool is_enlarged = false;

    SDL_Texture* texture = nullptr;

    SDL_Rect source_data;
    SDL_Rect destination_data;
};

/**
 * @brief Handles the creation and rendering of sprites to the screen.
 * 
 * Sprites can be rendered to the screen using the render() method.
 * 
 * @attention Sprites MUST be creation using the SpriteHandler, else each 
 * Sprite's texture will be a nullptr
 */
class SpriteHandler
{

public:

    SpriteHandler();
    SpriteHandler(TextureHandler* _texture_handler);

    /**
     * @brief Buffers a sprite to render on the next render call at a position
     * 
     * @param s Sprite to render
     * @param x X position in pixels
     * @param y Y position in pixels
     */
    void render_sprite(Sprite* s, int x, int y);

    /**
     * @brief Render all flagged sprites to the screen.
     */
    void render();

    /**
     * @brief Clears buffered sprites before they are rendered to the screen
     * 
     */
    void clear();

    void set_size_multiplier(float new_multiplier);

    float get_size_multiplier() const;

    /**
     * @brief Creates a Sprite.
     * 
     * @attention The Sprite is created on heap memory, and it is the user's 
     * responsiblity to handle this memory 
     * 
     * @param _sprite_path Path to the png 
     * @param source_x X position in the png file
     * @param source_y Y position in the png file
     * @param source_width Width of the splice of the png file
     * @param source_height Height of the splice of the png file
     * @param destination_width Width to render the sprite on the screen
     * @param destination_height Height to render the sprite on the screen
     */
    Sprite* create_sprite(const char* _sprite_path, int source_x, 
        int source_y, int source_width, int source_height,
        int destination_width, int destination_height,
        bool enlarge_sprite = true);

private:

    /**
     * @brief Contains the info needed to render a Sprite to the screen
     * 
     */
    struct SpriteRenderDataContainer
    {
        Sprite* sprite; // Target Sprite
        int x_pos; // X position on the screen
        int y_pos; // Y position on the screen
    };

    /**
     * Sprite dimensions and positions will be multipled by this number when 
     * output
     */
    float sprite_size_multiplier = 1.0;

    /**
     * Queue of Sprites that will be rendered to the screen on the next 
     * render() call
     */
    std::queue<SpriteRenderDataContainer> sprites_to_render;

    /**
     * A map of the png directories to their respective SDL_Texture objects.
     * This map exists in the case where a png in question is a spritesheet 
     * with multiple sprites, so that when these multiple sprites attempt to 
     * all create a SDL_Texture from the same path, only one SDL_Texture object
     * will be created, and it will be shared between each Sprite.
     */
    static std::unordered_map<const char*, SDL_Texture*> 
        sprite_paths_to_textures;

    TextureHandler* texture_handler;
};