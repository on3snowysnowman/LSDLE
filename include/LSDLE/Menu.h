#pragma once

#include <string>
#include <queue>

#include "InstructionSequence.h"


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

    Menu() {}

    
    /**
     * @brief Sets the instruction queue of this Menu.
     * 
     * 
     * @param _instruction_queue 
     */
    void set_instruction_queue(std::queue<InstructionSequence>* 
        _instruction_queue)
    {
        instruction_queue = _instruction_queue;
    }

    /**
     * @brief Called when the Menu is activated.
     * 
     * Logic that needs to be run once, such as the instanciation and 
     * definition of variables should be placed here. 
     */
    virtual void start() {}

    /**
     * @brief Called each frame if the Menu is activated.
     * 
     * This is where the majority of the Menu's logic should go.
     */
    virtual void update() {}

    /**
     * @brief Flags this Menu as activated.
     */
    void flag_activated() { activated = true; }

    /**
     * @brief Flags this Menu as not activated
     */
    void flag_deactivated() { activated = false; }

    /**
     * @brief Returns true if this Menu is activated
     */
    bool is_activated() { return activated; }

    /**
     * @brief Returns the unique identifier of this Menu
     */
    std::string get_id() const { return menu_id; }

protected:

    /**
     * If this Menu is activated and being updated each frame. This boolean's
     * logic is controlled explicitly by the MenuHandler through the 
     * flag_activated() and flag_deactivated() methods.
     */
    bool activated = false;

    // Unique string identifier
    std::string menu_id = "BaseMenu";

    /**
     * The instruction_queue points to the instruction queue object in the 
     * MenuHandler class. Menus will place InstructionSequences inside this 
     * queue, and the MenuHandler will read and process them each frame. This 
     * is how the Menus are able to communicate with the MenuHandler without
     * needed to include the MenuHandler, causing circular imports.
     */
    std::queue<InstructionSequence>* instruction_queue;
};
