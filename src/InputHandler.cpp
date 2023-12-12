#include <algorithm>

#include "InputHandler.h"

// ---------------------InputHandler-------------------------------------------

// Constructors / Deconstructor

InputHandler::InputHandler() {}


// Public

void InputHandler::update()
{
    raw_keys.clear();

    // Iterate through each delayed key
    for(std::list<uint32_t>::iterator it = delayed_keys.begin(); 
        it != delayed_keys.end(); ++it)
    {
        /**
         * If this key's frames delayed is set to -1, it is blocked until the
         * key is released
         */
        // if(key_data.at(*it).frames_delayed == -1) continue;

        // Deduct 1 from its frame delay
        --key_data.at(*it).frames_delayed;
        
        // If the key no longer has a frame delay
        if(key_data.at(*it).frames_delayed <= 0)
        {
            // Remove it from the delayed keys list
            delayed_keys.erase(it);
            --it;
        }
    }
}

void InputHandler::flag_key_pressed(uint32_t key)
{   
    key_data[key].key_id = key;
    key_data[key].is_pressed = true;

    raw_keys.push_back(key);
}

void InputHandler::flag_key_released(uint32_t key)
{
    // If this key had a frame delay to it
    if(key_data[key].frames_delayed > 0) 
    {
        // Remove it from the delayed keys list
        remove_key_from_delayed_keys(key);
    }

    key_data[key].frames_delayed = 0;
    key_data[key].is_pressed = false;
}

void InputHandler::set_delay(uint32_t key, uint16_t frame_amount)
{
    /**
     * If this key didn't have a frame delay to it, it is known that it is not
     * currently present in the delayed keys list and needs to be added
     */
    if(key_data[key].frames_delayed == 0) delayed_keys.push_back(key);

    key_data[key].frames_delayed = frame_amount;
}

void InputHandler::block_key_until_released(uint32_t key)
{
    key_data[key].frames_delayed = -1;
}

void InputHandler::clear()
{
    // Iterate through each delayed key
    for(uint32_t key : delayed_keys)
    {
        // Set its frame delay to 0
        key_data[key].frames_delayed = 0;
    }

    delayed_keys.clear();
}

bool InputHandler::is_key_pressed(uint32_t key)
{
    return key_data[key].is_pressed;
}

bool InputHandler::is_key_pressed_and_available(uint32_t key)
{
    return key_data[key].is_pressed && key_data[key].frames_delayed == 0;
}

uint16_t InputHandler::get_delay_amount(uint32_t key)
{
    return key_data[key].frames_delayed;
}

std::vector<uint32_t> InputHandler::get_all_pressed_keys(bool sort) const
{
    std::vector<uint32_t> pressed_keys;

    for(auto& pair : key_data)
    {
        if(pair.second.is_pressed) pressed_keys.push_back(pair.first);
    }

    if(sort) std::sort(pressed_keys.begin(), pressed_keys.end());

    return std::move(pressed_keys);
}

std::vector<uint32_t> InputHandler::
    get_all_pressed_and_available_keys(bool sort) const
{
    std::vector<uint32_t> pressed_keys;

    for(auto& pair : key_data)
    {
        if(pair.second.is_pressed && pair.second.frames_delayed == 0)
        {
            pressed_keys.push_back(pair.first);
        } 
    }

    if(sort) std::sort(pressed_keys.begin(), pressed_keys.end());

    return std::move(pressed_keys);
}

const std::vector<uint32_t>& InputHandler::get_raw_keys() const
{
    return raw_keys;
}


// Private

void InputHandler::remove_key_from_delayed_keys(uint32_t key)
{
    for(std::list<uint32_t>::iterator it = delayed_keys.begin(); 
        it != delayed_keys.end(); ++it)
    {
        if(key == (*it)) 
        {
            delayed_keys.erase(it);
            break;
        }
    }   
}


// ---------------------Key----------------------------------------------------

// Constructors / Deconstructor 

InputHandler::Key::Key() {}

