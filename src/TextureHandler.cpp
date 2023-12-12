#include <SDL2/SDL_image.h>
#include <sstream>

#include "TextureHandler.h"
#include "Debug.h"
#include "Json.h"
#include "JsonLoader.h"


// Static Members

std::string TextureHandler::color_data_path;

std::unordered_map<std::string, Color> TextureHandler::colors; 


// Constructors / Deconstructor

TextureHandler::TextureHandler()
{
    renderer = nullptr;
}

TextureHandler::TextureHandler(SDL_Renderer* _renderer, std::string _color_data_path)
{
    renderer = _renderer;
    color_data_path = _color_data_path;
    register_colors();
}


// Public

void TextureHandler::draw(SDL_Texture* texture, SDL_Rect& source, 
    SDL_Rect& dest) const
{
    // Draw to the screen
    SDL_RenderCopy(renderer, texture, &source, &dest);
}

void TextureHandler::draw_with_color(SDL_Texture* texture, SDL_Rect& source,
    SDL_Rect& dest, std::string color) const
{
    // If the color is not in the colors map
    if(colors.find(color) == colors.end())
    {
        std::stringstream message;

        message << "TextureHandler.draw_with_color(SDL_Texture* texture, "
            << "SDL_Rect& source, SDL_Rect& dest, std::string color) "
            << "where 'color' = " << color << " -> Color doesn't "
            << "exist.";

        Debug::log(message.str(), Debug::ERR);
        exit(0);
    }

    Color* targ_color = &colors.at(color);

    // Store the original color modulation values
    SDL_Color originalColor;
    SDL_GetTextureColorMod(texture, &originalColor.r, &originalColor.g, &originalColor.b);

    // Apply the color to the texture
    SDL_SetTextureColorMod(texture, targ_color->r, targ_color->g, 
        targ_color->b);

    // Draw to the screen
    SDL_RenderCopy(renderer, texture, &source, &dest);

    // Restore the original color modulation values
    SDL_SetTextureColorMod(texture, originalColor.r, originalColor.g, originalColor.b);
}

SDL_Texture* TextureHandler::create_texture(const char* path) const
{
    // Path file doesn't exist
    if(!Debug::does_directory_exist(path))
    {
        std::string message = 
            "TextureHandler.create_texture(const char* path) where 'path' = "
            + std::string(path) + " -> Failed to open file";

        Debug::log(message, Debug::ERR);
        exit(EXIT_FAILURE);
    }

    SDL_Surface* temp_surface = IMG_Load(path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temp_surface);

    SDL_FreeSurface(temp_surface);

    return texture;
}


// Private

void TextureHandler::register_colors()
{
    // Get the color data from the data path
    Json color_data = JsonLoader::get(color_data_path.c_str());

    // Iterate through each color array in the Json file
    for(Json color : color_data)
    {
        // Create a Color object and place it in the colors map with the 
        // color's name as the key
        colors.emplace(color.at(3), Color(color.at(0), color.at(1),
            color.at(2), color.at(3)));
    }
}
