#pragma once

#include <string>

#include "MenuToolItem.h"
#include "../ConsoleOutputHandler.h"
#include "../InputHandler.h"
#include "MenuToolText.h"
#include "Window.h"


/**
 * @brief A MenuToolItem, used in the MenuTools' menu simulation.
 * 
 * The MenuToolTextList contains a list of MenuToolText items. The user may 
 * modify these Text items, along with adding more or deleting them.
 * 
 */
class MenuToolTextList : public MenuToolItem
{

public:

    MenuToolTextList();
    MenuToolTextList(Window* window, std::string _cursor_color, 
        std::string _name, uint16_t _cursor_pos = 0, int32_t _selected_pos = -1);
    
    void reset() final;

    /**
     * @brief Render the TextList with the understanding that it has no status
     * (it is not hovered or selected)
     */
    void render_no_status() const final;

    /**
     * @brief Render the TextList with the understanding it is hovered by the 
     * cursor.
     */
    void render_hovered() const final;

    /**
     * @brief Render the TextList with the understanding it is selected
     */
    void render_selected() const final;

    /**
     * @brief Handles the input from the user while selected. This includes
     * the navigation of the text list, along with the selection of Text items 
     * and the "Add Text" button.
     */
    Status handle_input() final;

    // Index of the cursor in the content list
    uint16_t cursor_pos = 0;
    
    // Index of the Text that is selected. -1 means no Text is selected
    int32_t selected_pos = -1;

    // Name of this list
    std::string name;

    // The MenuToolText items this list contains
    std::vector<MenuToolText> content;

};