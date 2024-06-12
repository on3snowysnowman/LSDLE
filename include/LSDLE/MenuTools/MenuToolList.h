#pragma once

#include <string>

#include "MenuToolItem.h"
#include "../ConsoleOutputHandler.h"
#include "../InputHandler.h"
#include "Window.h"


/**
 * @brief A MenuToolItem, used in the MenuTools' menu simulation.
 * 
 * The MenuToolList is able to store other MenuToolItems in a list
 * format, and allow the user to navigate this list the same way they 
 * are navigating the list of the menu simulation. The items in this list
 * can be edited the same way as if they were in the root of the menu 
 * simulation list.  
 * 
 */
class MenuToolList : public MenuToolItem
{

public:

    MenuToolList();
    MenuToolList(Window* window, std::string _cursor_color, 
        std::string _name, uint16_t _cursor_pos = 0, 
        int32_t _selected_pos = -1);

    void reset() final;

    /**
     * @brief Render the List with the understanding that it has no status
     * (it is not hovered or selected)
     */    
    void render_no_status() const final;

    /**
     * @brief Render the List with the understanding it is hovered by the 
     * cursor.
     */
    void render_hovered() const final;

    /**
     * @brief Render the Choice with the understanding it is selected
     */
    void render_selected() const final;

    /**
     * @brief Handles the input from the user when selected. This includes
     * the navigation of this List, along with being able to select the Items
     * inside as well.
     */
    Status handle_input() final;

    // Index of the cursor in the content list
    uint16_t cursor_pos = 0;

    // Index of the Item that is selected. -1 means no Item is selected
    int32_t selected_pos = -1;

    // Name of this list
    std::string name;

    // The MenuToolItems this List contains
    std::vector<MenuToolItem*> content;
};
