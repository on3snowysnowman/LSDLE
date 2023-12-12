#include <cmath>
#include <fstream>
#include <Debug.h>

#include "Json.h"
#include "JsonLoader.h"
#include "TextDisplayHandler.h"


// Constructors / Deconstructor

TextDisplayHandler::TextDisplayHandler()
{
    texture_handler = nullptr;
}

TextDisplayHandler::TextDisplayHandler(TextureHandler* _texture_handler)
{
    texture_handler = _texture_handler;

    std::fstream file_stream("path.txt", std::ios::in);

    if(!file_stream.is_open())
    {
        Debug::log("TextDisplayHandler.TextDisplayHandler() -> Could not open "
            "file : path.txt");
    }

    std::string LSDLE_project_path;

    std::getline(file_stream, LSDLE_project_path);


    // Load the font data

    Json font_data = JsonLoader::get((LSDLE_project_path + '/' + 
        std::string(font_path)).c_str());

    // Get font dimensions
    font_width = font_data["font_width"];
    font_height = font_data["font_height"];


    // Create the texture from the font png path
    font_texture = texture_handler->create_texture(
        std::string(LSDLE_project_path + '/' + 
            std::string(font_data["png_path"])).c_str());

    // Iterate through each character in the character data
    for(Json char_data : font_data["character_data"])
    {
        char targ_char = std::string(char_data.at(0)).at(0);

        std::pair<uint8_t, uint8_t> char_pos {char_data.at(1), 
            char_data.at(2)};

        // Add this char's position in the png file to the map
        char_source_positions.emplace(targ_char, char_pos);
    }
}


// Public

void TextDisplayHandler::add_ch(char character, int x_pos, int y_pos) 
{    
    _add_ch(character, x_pos, y_pos);
}

void TextDisplayHandler::add_ch(char character, int x_pos, int y_pos,
    std::string color)
{
    _add_ch(character, x_pos, y_pos, color);
}

void TextDisplayHandler::add_str(std::string str, int x_pos, int y_pos) 
{
    _add_str(str, x_pos, y_pos);
}

void TextDisplayHandler::add_str(std::string str, int x_pos, int y_pos,
    std::string color)
{
    _add_str(str, x_pos, y_pos, color);
}

void TextDisplayHandler::clear_buffer()
{
    while(!queued_characters.empty())
    {
        queued_characters.pop();
    }
}

void TextDisplayHandler::render()
{
    while(!queued_characters.empty())
    {

        // Fetch the next character in the queue
        QueuedRenderedCharacter& targ_char = queued_characters.front();
        queued_characters.pop();
        
        // Get the characters position in the font texture
        std::pair<uint8_t, uint8_t>& character_source_position
            = char_source_positions.at(targ_char.symbol);

        // Create an SDL Rect for the source data of this char
        SDL_Rect source_data {character_source_position.first, 
            character_source_position.second, font_width, font_height};
       
        // Get the SDL Rect for the destination data of this char
        SDL_Rect& destination_data = targ_char.destination;

        // If this character is colored
        if(targ_char.colored)
        {
            // Draw the character with the color
            texture_handler->draw_with_color(font_texture, source_data, 
                destination_data, targ_char.color);
        }

        else
        {
            // Draw the character
            texture_handler->draw(font_texture, source_data, destination_data);
        }
        
    }
}

uint8_t TextDisplayHandler::get_raw_font_width() { return font_width; }

uint8_t TextDisplayHandler::get_raw_font_height() { return font_height; }

uint8_t TextDisplayHandler::get_scaled_font_width() 
{ 
    return get_scaled_size_value(font_width); 
}

uint8_t TextDisplayHandler::get_scaled_font_height()
{
    return get_scaled_size_value(font_height);
}


// Private

void TextDisplayHandler::_add_ch(char character, int x_pos, int y_pos,
    std::string color)
{
    if(character == '\n' || character == ' ') return;

    // Make an SDL Rect with the position and dimensions
    SDL_Rect destination {x_pos, y_pos, 
        get_scaled_size_value(font_width),
        get_scaled_size_value(font_height)};
    
    // Queue the character to be rendered on next render call
    queued_characters.push(QueuedRenderedCharacter(character, destination, 
        color));
}

void TextDisplayHandler::_add_str(std::string str, int x_pos, int y_pos,
    std::string color)
{
    int current_x = x_pos;

    for(char c : str)
    {
        if(c == ' ')
        {
            current_x += get_scaled_size_value(font_width);
            continue;
        }

        _add_ch(c, current_x, y_pos, color);

        current_x += get_scaled_size_value(font_width);
    }
}

int TextDisplayHandler::get_scaled_size_value(int initial_size)
{
    return int(std::ceil(initial_size * font_size_multiplier));
}


// ---------- QueuedRenderedCharacter -----------------------------------------

// Constructors / Deconstructor

TextDisplayHandler::QueuedRenderedCharacter::
    QueuedRenderedCharacter(char _symbol, SDL_Rect& _destination, 
    std::string _color)
{
    symbol = _symbol;
    destination = _destination;
    color = _color;

    if(color.size() != 0) colored = true;
}
