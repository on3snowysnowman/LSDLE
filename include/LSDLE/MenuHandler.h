#pragma once

#include <queue>
#include <list>
#include <unordered_map>

#include "Menu.h"
#include "InstructionSequence.h"


/**
 * @brief The MenuHandler manages every Menu instance during the simulation, 
 * along with tacking each Menu that is currently activated. It is also in 
 * charge of activating and deactivating Menus. This is either done manually
 * through direct calls of the activate and deactivate menu methods, or can
 * be done automatically through individual Menus sending instructions to 
 * the MenuHandler to do so inside their pointer to this class's instruction
 * queue.
 * 
 * Each frame, the MH updates all activated Menu's update() method, along with 
 * parsing and processing each InstructionSequence in the instruction_queue.
 * 
 * For an in depth explanation of the specific instructions the MenuHandler may
 * parse, read "documentatino/Setup_and_Uses.txt" : "Part 10 : Menus".
 */
class MenuHandler
{

public:

    MenuHandler();

    /**
     * @brief Updates each activated Menu, along with parsing the instruction
     * queue and processing each InstructionSequence
     */
    void update();

    /**
     * @brief Registers a Menu with the MenuHandler, with the Menu as a 
     * parameter.
     * 
     * @param m Target Menu
     */
    void register_menu(Menu* m);

    /**
     * @brief Activates a Menu. The MenuHandler will parse its known Menus 
     * until it finds the one with the passed menu_id, and will activate it.
     * 
     * @param menu_id Id of the target Menu
     */
    void activate_menu(std::string menu_id);

    /**
     * @brief Activates the passed Menu.
     * 
     * @param m Target Menu.
     */
    void activate_menu(Menu* m);
    
    /**
     * @brief Deactivates a Menu. The MenuHandler will parse its known Menus 
     * until it finds the one with the passed menu_id, and will deactivate it.
     * 
     * @param menu_id Id of the target Menu
     */
    void deactivate_menu(std::string menu_id);

    /**
     * @brief Deactivates the passed Menu.
     * 
     * @param m Target Menu
     */
    void deactivate_menu(Menu* m);

    /**
     * @brief Returns the instance of the menu with the passed menu id. This is
     * assuming that the menu exists and has been registered with the 
     * MenuHandler. If the menu can't be found, a nullptr is returned.
     * 
     * @param menu_id Id of the menu to return
     */
    Menu* get_menu(std::string menu_id);

private:

    /**
     * Queue of instructions that will be parsed each frame. A pointer to this
     * queue is passed to each registered Menu, so that those Menus may create
     * and place InstructionSequences directly into this queue for the 
     * MenuHandler to read.
     */
    std::queue<InstructionSequence> instruction_queue;

    /**
     * List of Menus that are currently active. The MenuHandler will parse
     * this list each frame and update each Menu in it.
     */
    std::list<Menu*> active_menus;

    /**
     * All Menus that are registered with the MenuHandler, with their ids
     * as keys.
     */
    std::unordered_map<std::string, Menu*> registered_menus;

    /**
     * @brief Processes the passed instruction sequence.
     * 
     * @param i Target instruction sequence
     */
    void process_instruction(InstructionSequence& i);

    /**
     * @brief Gets the next instruction in the InstructionSequence
     * 
     * @param i Target InstructionSequence
     */
    std::string get_next_instruction(InstructionSequence& i) const;
};