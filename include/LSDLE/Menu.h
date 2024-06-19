#pragma once

#include <string>
#include <queue>
#include <cstdint>

// #include "InstructionSequence.h"
#include "Window.h"
#include "MenuTools.h"
#include "InputHandler.h"

/**
 * @brief Base class for creating derived menus with specific logic.
 * 
 * Menus are handled and updated using the MenuHandler. The start() method is 
 * called on Menu activation, and the update() method is called once per 
 * frame if the Menu is activated. Each Menu has a unique string identifier 
 * which the MenuHandler uses to track and manage each Menu. Menus can 
 * communicate with the MenuHandler through the instruction queue. 
 * InstructionSequences can be placed inside the queue and are processed by 
 * the MenuHandler each frame. If Menus are activated, they will be updated 
 * each frame by the MenuHandler. It's recommended to use the logic inside the
 * MenuTools.h file to create and build the UI and user input handling for 
 * these menus, as they were created for methods that are cycled through each 
 * frame, instead of a stop-and-wait-for-input style of method.
 */
class Menu
{

public:

    Menu(std::string menu_id);    

    Menu(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y,
        std::string menu_id);

    /**
     * @brief Called when the Menu is activated.
     * 
     * Logic that needs to be run once, such as the instanciation and 
     * definition of variables should be placed here. 
     */
    virtual void start();

    /**
     * @brief Called each frame if the Menu is activated.
     * 
     * This is where the majority of the Menu's logic should go.
     */
    virtual void update();

    // void set_menu_handler(MenuHandler* menu_handler);

    /**
     * @brief Flags this Menu as activated.
     */
    void flag_activated();

    /**
     * @brief Flags this Menu as not activated
     */
    void flag_deactivated();


    void deactivate_menu();

    /**
     * @brief Returns true if this Menu is activated
     */
    bool is_activated();

    /**
     * @brief Returns the unique identifier of this Menu
     */
    std::string get_id() const;

protected:

    /**
     * If this Menu is activated and being updated each frame. This boolean's
     * logic is controlled explicitly by the MenuHandler through the 
     * flag_activated() and flag_deactivated() methods.
     */
    bool activated = false;

    // Unique string identifier
    std::string menu_id = "BaseMenu";

    Window* window {};

    MenuTools* menu_tools {};

    InputHandler* input_handler {};
};
