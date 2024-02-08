#pragma once

#include <cstdint>

#include "../ConsoleOutputHandler.h"
#include "../InputHandler.h"
#include "MenuToolItem.h"
#include "../ColorString.h"
#include "SimulationDataContainers.h"
#include "Window.h"


/**
 * @brief Provides a menu like interface for simple list selections, 
 * or more complex and modular items such as menu simulation. Uses the 
 * ListSelectionDataContainer and MenuSimulationDataContainer structs 
 * for the data and configuration for the selection and simulation.
 * 
 * See "documentation/MenuTools.txt" for an in depth explanation.
 */
class MenuTools
{

public:

    MenuTools();
    MenuTools(Window* window);

    void render_colored_number(uint16_t num, uint16_t lower_bound, 
        uint16_t higher_bound, std::vector<std::string> colors = {"Red", 
            "Orange", "Yellow", "Green"});

    /**
     * @brief Provides a list selection to the user using an LSDC as the data
     * container. The simulate_list_selection parses the content of the 
     * LSDC and allows the user to make a selection from a multitude of 
     * predetermined choices. Depending on the input of the user at the time,
     * the LSDC will be modified and the changes can be monitored by the user 
     * outside of the function. See "documentation/MenuTools.txt" for an 
     * in depth explanation.
     */
    void simulate_list_selection(
        ListSelectionDataContainer& l_s_d_c);

    /**
     * @brief Provides a menu simulation for the user using a MSDC as the
     * data container. The simulate_menu parses the content of the MSDC, 
     * and allows the user to select and modify the MenuToolItems contained
     * in it. Specific functions of the modification process depends on what 
     * type of MenuToolItems exist in the content. Depending on the input of 
     * the user at the time, the MSDC will be modified and teh changes can be 
     * monitored by the user outside of the function. See 
     * "documentation/MenuTools.txt" for an in depth explanation.
     * 
     * @param m_s_d_c 
     */
    void simulate_menu(
        MenuSimulationDataContainer& m_s_d_c);


private:

    /**
     * @brief The render function for the list selection process. 
     * 
     * This function is split from the original list selection call simply
     * for the sake of readability
     */
    void render_list_selection(ListSelectionDataContainer& l_s_d_c);

    /**
     * @brief The input handling function for the list selection process.
     * 
     * This function is split from the original list selection call simply
     * for the sake of readability
     */
    void handle_list_selection_input(ListSelectionDataContainer& 
        l_s_d_c);

    /**
     * @brief The render function for the menu simulation process.
     * 
     * This function is split from the original menu simulation call simply
     * for the sake of readability.
     */
    void render_menu_simulation(MenuSimulationDataContainer& m_s_d_c);

    /**
     * @brief The input handling function for the menu simulation process.
     * 
     * This function is split from the original menu simulation call simply
     * for the sake of readability.
     */
    void handle_menu_simulation_input(MenuSimulationDataContainer& m_s_d_c);

    InputHandler* input_handler;

    Window* window;
};
