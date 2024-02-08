#pragma once

#include "MenuToolItem.h"
#include "../ConsoleOutputHandler.h"
#include "../InputHandler.h"
#include "Window.h"


/**
 * @brief A MenuToolItem, used in the MenuTools' menu simulation.
 * 
 * The MenuToolChoice provides a "choice" item to the user. When the 
 * Choice is selected, a drop down menu of pre determined choices are
 * provided to the user, and they can select one of the list. 
 * 
 */
class MenuToolChoice : public MenuToolItem
{

public:


    MenuToolChoice();
    MenuToolChoice(Window* window, std::string _cursor_color, 
        std::string _name, uint8_t _choice_index);

    /**
     * @brief Render the Choice with the understanding that it has no status
     * (it is not hovered or selected)
     */
    void render_no_status() const final;

    /**
     * @brief Render the Choice with the understanding it is hovered by the 
     * cursor.
     */
    void render_hovered() const final;

    /**
     * @brief Render the Choice with the understanding it is selected
     */
    void render_selected() const final;

    /**
     * @brief Handles the input from the user while selected. This includes
     * navigating the choice list and selecting them.
     */
    Status handle_input() final;

    // Index of the current choice in the content list
    uint8_t choice_index;

    // Index of the cursor in the content list
    uint8_t cursor_index;

    // Name of the choice selections
    std::string name;

    // // Color of the cursor
    // std::string cursor_color;

    // List of the choices
    std::vector<ColorString> choices;
};
