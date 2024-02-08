#pragma once

#include <string>

#include "MenuToolItem.h"
#include "../ConsoleOutputHandler.h"
#include "../InputHandler.h"
#include "SimulationDataContainers.h"
#include "Window.h"


/**
 * @brief A MenuToolItem, used in the MenuTools' menu simulation.
 * 
 * The MenuToolButton acts as a selectable button for the user to "select".
 * Other than being able to be selected, the button has no further purpose.
 * This acts as a "flag" for whatever is handling the menu simulation's 
 * output that this button has been pressed, and they may want to run 
 * logic in accordance to that happening.
 */
class MenuToolButton : public MenuToolItem
{

public:

    MenuToolButton();
    MenuToolButton(Window* window, std::string _name, 
        std::string cursor_color, std::string _button_color = "White");
    
    /**
     * @brief Render the Button with the understanding that it has no status
     * (it is not hovered or selected)
     */
    void render_no_status() const final;

    /**
     * @brief Render the Button with the understanding it is hovered by the 
     * cursor.
     */
    void render_hovered() const final;

    /**
     * @brief Render the Button with the understanding it is selected
     */
    void render_selected() const final;

    /**
     * @brief The Button does not handle any user input. It returns the 
     * HOVERED status since the Button does not need to remain selected 
     * after it has been pressed.
     */
    Status handle_input() final;

    std::string name;
    std::string button_color;
};
