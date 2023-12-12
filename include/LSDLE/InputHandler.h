#pragma once

#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <vector>

/**
 * @brief Tracks pressed keys from the user and can assign a delay to them so
 * the key is only active per an arbitrary amount of frames.
 */
class InputHandler
{

public:

    InputHandler();

    /**
    * @brief Deducts 1 frame from each key that has a frame delay
    * 
    * @attention Must be called each frame for InputHandler to function
    */
    void update();

    /**
     * @brief Flags a key as pressed.
     * 
     * @param key Target key
     */
    void flag_key_pressed(uint32_t key);

    /**
     * @brief Flags a key as released
     * 
     * @param key 
     */
    void flag_key_released(uint32_t key);

    /**
     * @brief Sets a frame delay for a key
     * 
     * @param key Target key
     * @param frame_delay Amount of frames
     */
    void set_delay(uint32_t key, uint16_t frame_amount = 12);

    /**
     * @brief Blocks a pressed key until it is released.
     * 
     * @param key Target key
     */
    void block_key_until_released(uint32_t key);

    /**
     * @brief Clear the frame delays for all keys
     */
    void clear();

    /**
     * @brief Returns true if a key is currently pressed.
     * 
     * @attention Note that this function returns true if a key is
     * pressed, regardless if it has a delay or not. 
     * 
     * @param key Target key
     */
    bool is_key_pressed(uint32_t key);

    /**
     * @brief Returns true if a key is currently pressed, and does not
     * have a frame delay.
     * 
     * @param key Target key
     */
    bool is_key_pressed_and_available(uint32_t key);

    /**
     * @brief Returns the amount of frames a key is currently delayed
     * 
     * @param key Target key
     */
    uint16_t get_delay_amount(uint32_t key);

    /**
     * @brief Returns all keys that are currently pressed with no regard
     * to frame delay. Can optionally be sorted.
     * 
     * @param sort If the return vector should be sorted
     */
    std::vector<uint32_t> get_all_pressed_keys(bool sort = false) const;

    /**
     * @brief Returns all keys that are currently pressed that have no frame 
     * delay to them. Can optionally be sorted.
     * 
     * @param sort If the return vector should be sorted
     */
    std::vector<uint32_t> get_all_pressed_and_available_keys(bool sort = false)
        const;

    /**
     * @brief Returns the keys that have only been registered as pressed this
     * frame. This method produces key press functions similar to when you're 
     * editing a text document, where there is a small delay after you press a 
     * key before the rest input.
     */
    const std::vector<uint32_t>& get_raw_keys() const;


private:
    
    class Key
    {
    
    public:

        Key();

        bool is_pressed = false; // If this key is currently pressed
        uint32_t key_id = 0; // ASCII value of the key
        uint16_t frames_delayed = 0; // How many frames this key is delayed
    };

    void remove_key_from_delayed_keys(uint32_t key);

    // Keys that are registered as pressed this frame only. 
    std::vector<uint32_t> raw_keys;

    // Keys that are currently delayed
    std::list<uint32_t> delayed_keys; 

    // ASCII values to their respective key objects 
    std::unordered_map<uint32_t, Key> key_data;  
};


