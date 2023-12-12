#pragma once

#include <string>

#include "MenuToolItem.h"
#include "../ConsoleOutputHandler.h"
#include "../InputHandler.h"
#include "SimulationDataContainers.h"


/**
 * @brief A MenuToolItem, used in the MenuTools' menu simulation.
 * 
 * The MenuToolText is an editable piece of text that the user may modify.
 * 
 */
class MenuToolText : public MenuToolItem
{

public:

    MenuToolText();
    MenuToolText(ConsoleOutputHandler* _console_output_handler,
        InputHandler* _input_handler, std::string cursor_color,
        std::string _content);

    /**
     * @brief Render the Text with the understanding that it has no status
     * (it is not hovered or selected)
     */
    void render_no_status() const final;

    /**
     * @brief Render the Text with the understanding it is hovered by the 
     * cursor.
     */
    void render_hovered() const final;

    /**
     * @brief Render the Text with the understanding it is selected
     */
    void render_selected() const final;
    
    /**
     * @brief Handles the input from the user while selected. This includes
     * adding and deleting characters from the Text content.
     * 
     * @return Status 
     */
    Status handle_input() final;

    // The content of the Text
    std::string content;

};