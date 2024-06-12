#pragma once

#include <string>
#include <cstdint>
#include <vector>
#include <initializer_list>

#include "../ColorString.h"
#include "MenuToolItem.h"

/**
 * @brief The ListSelectionDataContainer is purely a storage struct. It contains
 * data that will be used by the MenuTools' list selection method. An instance
 * of the LSDC will be passed into the list selection method by reference, and 
 * the list selection method makes changes to it that the user can monitor 
 * outside of the method.
 */
struct ListSelectionDataContainer
{

    ListSelectionDataContainer() {}
    ListSelectionDataContainer(std::string _cursor_color, 
        uint8_t _cursor_pos = 0, bool _block_enter_key = true)
    {
        cursor_color = _cursor_color;
        cursor_pos = _cursor_pos;
        block_enter_key = _block_enter_key;
    }
    
    // If the enter key will be blocked until released on button presses
    bool block_enter_key = true;

    /**
     * If an item in the content has been selected
     */
    bool item_has_been_selected = false;

    // Position of the cursor in the content
    uint8_t cursor_pos {};
    
    // Color of the cursor
    std::string cursor_color;

    // The choices of the List Selection Menu
    std::vector<ColorString> content;

    void reset()
    {
        cursor_pos = 0;
        item_has_been_selected = false;
    }

    const std::string& get_selected_item() const
    {
        return content.at(cursor_pos).content;
    }
};


/**
 * @brief The MenuSimulationDataContainer is purely a storage struct. It 
 * contains data that will be used by the MenuTools' menu simulation method. An 
 * instance of the MSDC will be passed into the menu simulation method by 
 * reference, and the menu simulation method makes changes to it that the user 
 * can monitor outside of the method.
 */
struct MenuSimulationDataContainer
{

    MenuSimulationDataContainer() 
    {
        cursor_pos = 0;
        selected_pos = -1;
        block_enter_key = true;
    }

    MenuSimulationDataContainer(uint8_t _cursor_pos, 
        int16_t _selected_position, bool _block_enter_key)
    {
        cursor_pos = _cursor_pos;
        selected_pos = _selected_position;
        block_enter_key = _block_enter_key;
    }

    void reset()
    {
        cursor_pos = 0;
        selected_pos = -1;
    }

    void reset_contents()
    {
        for(MenuToolItem* item : content)
        {
            item->reset();
        }
    }

    void fill_content(std::initializer_list<MenuToolItem*> menu_items)
    {
        for(MenuToolItem* item : menu_items)
        {
            content.push_back(item);
        }
    }

    // If the enter key will be blocked until released on button presses
    bool block_enter_key = true;
    
    // Position of the cursor in the content
    uint8_t cursor_pos {};

    /**
     * Position of the selected item in the content. If there is no item 
     * selected, the index will be -1
     */
    int16_t selected_pos {};

    // Content of the Menu simulation
    std::vector<MenuToolItem*> content;
    
};