#include "SpriteHandler.h"
#include "LSDLE.h"

// Static Members

std::unordered_map<const char*, SDL_Texture*> 
    SpriteHandler::sprite_paths_to_textures;

TextureHandler* SpriteHandler::texture_handler {};

// --------------------SPRITE--------------------------------------------------

Sprite::Sprite() {}


// ------------------SPRITE_HANDLER--------------------------------------------

// Constructors / Deconstructor

SpriteHandler::SpriteHandler() 
{
    texture_handler = LSDLE::get_texture_handler();
}


#include <iostream>
// Public

void SpriteHandler::render_sprite(Sprite* s, int x, int y)
{   
    SpriteRenderDataContainer s_r_d_c{s, x, y};

    sprites_to_render.push(s_r_d_c);
}

void SpriteHandler::render()
{
    while(!sprites_to_render.empty())
    {
        SpriteRenderDataContainer sprite_container = sprites_to_render.front();
        sprites_to_render.pop();

        SDL_Rect dest = sprite_container.sprite->destination_data;

        // Alter the destination data to reflect the data in the data container
        dest.x = sprite_container.x_pos;
        dest.y = sprite_container.y_pos;

        // If the sprite should be enlarged with the size multiplier
        if(sprite_container.sprite->is_enlarged)
        {
            // Enlarge the sprite with its new position
            std::ceil(dest.x *= sprite_size_multiplier);
            std::ceil(dest.y *= sprite_size_multiplier);

            std::ceil(dest.w *= sprite_size_multiplier);
            std::ceil(dest.h *= sprite_size_multiplier);
        }

        // std::cout << "Drawing Sprite : (" << sprite_container.sprite->source_data.x << 
        //     ", " << sprite_container.sprite->source_data.y << ", " << sprite_container.sprite->source_data.w
        //     << ", " << sprite_container.sprite->source_data.h << ") - (" << dest.x << ", " << dest.y
        //     << ", " << dest.w << ", " << dest.h << ")\n";

        // exit(0);

        texture_handler->draw(sprite_container.sprite->texture,
            sprite_container.sprite->source_data, 
            dest);
    }
}

void SpriteHandler::clear()
{
    while(!sprites_to_render.empty())
    {
        sprites_to_render.pop();
    }
}

void SpriteHandler::set_size_multiplier(float new_multiplier)
{
    sprite_size_multiplier = new_multiplier;
}

float SpriteHandler::get_size_multiplier() const
{
    return sprite_size_multiplier;
}

Sprite* SpriteHandler::create_sprite(const char* _sprite_path, int source_x, 
    int source_y, int source_width, int source_height, 
    int destination_width, int destination_height, bool enlarge_sprite)
{
    Sprite* new_s = new Sprite();

    new_s->is_enlarged = enlarge_sprite;

    SDL_Texture* texture;

    // A texture has already been created using the png at this path
    if(sprite_paths_to_textures.find(_sprite_path) != 
        sprite_paths_to_textures.end())
    {
        // Use the already created texture
        texture = sprite_paths_to_textures.at(_sprite_path);
    }

    // No texture has been created for this path
    else
    {
        // Create the texture and register it with its path

        texture = texture_handler->create_texture(_sprite_path);
        sprite_paths_to_textures.emplace(_sprite_path, texture);
    }

    // Set the new Sprite's texture

    new_s->texture = texture;

    // Set the rendering data for the sprite

    new_s->source_data.x = source_x;
    new_s->source_data.y = source_y;
    new_s->source_data.w = source_width;
    new_s->source_data.h = source_height;

    new_s->destination_data.x = 0;
    new_s->destination_data.y = 0;

    new_s->destination_data.w = destination_width; 
    new_s->destination_data.h = destination_height;

    return new_s;
}


// Private
