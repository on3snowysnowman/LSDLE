#pragma once

#include <unordered_map>

#include "ConsoleOutputHandler.h"
#include "../InputHandler.h"
#include "SimulationDataContainers.h"
#include "MenuToolItemType.h"
#include "Window.h"


/**
 * @brief MenuToolItems are used in the MenuTool's menu simulation. This
 * class provides the base for multiple different classes to derive 
 * from and implement their own logic for use in the menu simulation.
 * 
 * Each class that derives from MenuToolItem will overload the three different
 * render methods, along with the handle_input() method. 
 */
class MenuToolItem
{

public:

    /**
     * Status of a MenuToolItem during menu simulation. NO_STATUS means there
     * is no status to the item, HOVERED means the item is hovered by the 
     * cursor, and SELECTED means this item is currently selected
     */
    enum Status
    {
        NO_STATUS, 
        HOVERED,
        SELECTED,
    };

    // Type of the content for items such as the Variable
    enum StringType
    {
        STRING,
        INT,
        FLOAT
    };

    MenuToolItem();
    MenuToolItem(Window* window, std::string _cursor_color, 
        ItemType _item_type);

    
    /**
     * @brief Render the Item with the understanding that it has no status
     * (it is not hovered or selected)
     */
    virtual void render_no_status() const;

    /**
     * @brief Render the Item with the understanding it is hovered by the 
     * cursor.
     */
    virtual void render_hovered() const;

    /**
     * @brief Render the Item with the understanding it is selected
     */
    virtual void render_selected() const;

    /**
     * @brief Handle user input. This logic will vary between different 
     * MenuToolItem derived classes.
     */
    virtual Status handle_input();

    /**
     * @brief Sets the cursor color to a color
     * 
     * @param color Color to set
     */
    void set_cursor_color(std::string color);

    /**
     * @brief Returns the cursor color
     */
    std::string get_cursor_color() const;

    /**
     * @brief Returns the type of this item
     */
    ItemType get_item_type() const;

protected:

    /**
     * @brief Takes an ASCII key and a string, and applies logic to the 
     * string based on the key passed. 
     * 
     * @param key Pressed key
     * @param str String to modify
     */
    void apply_input_to_string(uint32_t key, std::string& str);

    InputHandler* input_handler = nullptr;

    // Keys to their respective keys when used with the Shift Key
    static const std::unordered_map<char, char> KEYS_TO_SHIFTED_KEYS;

    // Color of the cursor
    std::string cursor_color;

    /**
     * Type of this Item. Default is TEXT but should change between derived
     * MenuToolItem classes
     */
    ItemType item_type = TEXT;

    Window* window;
};