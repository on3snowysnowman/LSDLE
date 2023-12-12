#pragma once

#include <SDL2/SDL.h>
#include <unordered_map>

#include "Color.h"

/**
 * @brief Handles the creation of Textures from PNG files, along with drawing 
 * things to the screen.
 * 
 * Must be created with a valid instance of the SDL_Renderer.
 * 
 */
class TextureHandler
{

public:

    TextureHandler();

    TextureHandler(SDL_Renderer* _renderer, std::string _color_data_path);

    /**
     * @brief Draws a portion of the texture to the screen.
     * 
     * The source SDL_Rect represents the dimensions that will be sliced from
     * the texture, while the dest SDL_Rect represents the dimensions that
     * will be displayed to the screen.  
     * 
     * @param texture Texture to draw
     * @param source Source dimensions to splice from the texture
     * @param dest Desination dimensions to draw to the sreen
    */
    void draw(SDL_Texture* texture, SDL_Rect& source, SDL_Rect& dest) const;

    /**
     * @brief Draw with color.
     * 
     * Same functionality as the draw method, but colors the texture with the 
     * passed color.
     * 
     * @param texture Texture to draw
     * @param source Source dimensions to splice from the texture
     * @param dest Desination dimensions to draw to the sreen
     * @param color Name of the color.
     */
    void draw_with_color(SDL_Texture* texture, SDL_Rect& source, 
        SDL_Rect& dest, std::string color) const;


    /**
     * Creates and returns an SDL_Texture from a png at the path file.
     * 
     * @param path Directory of the png.
    */
    SDL_Texture* create_texture(const char* path) const;


private:

    // Path to the color data json file
    static std::string color_data_path;

    // A map of Color names to their respective Color objects
    static std::unordered_map<std::string, Color> colors;

    SDL_Renderer* renderer;

    /**
     * @brief Creates and registers the colors from the color_data_path Json
     * file.
     */
    void register_colors();
};