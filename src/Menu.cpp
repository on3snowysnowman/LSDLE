#include "Menu.h"

#include "MenuHandler.h"
#include "LSDLE.h"


// Constructors / Deconstructors

Menu::Menu(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y,
    std::string _menu_id) 
{
    menu_id = _menu_id;

    window = new Window(start_x, start_y, end_x, end_y);

    menu_tools = new MenuTools(window);

    input_handler = LSDLE::get_input_handler();
    
    MenuHandler::register_menu(this);
}


// Public

// void Menu::set_instruction_queue(std::queue<InstructionSequence>*
//     instruction_queue)    
// {
//     instruction_queue = instruction_queue;
// }

void Menu::start() {}

void Menu::update() {}

// void Menu::set_menu_handler(MenuHandler* _menu_handler)
// {
//     m_handler = _menu_handler;
// }

void Menu::flag_activated() { activated = true; }

void Menu::flag_deactivated() { activated = false; }

bool Menu::is_activated()  { return activated; }

std::string Menu::get_id() const { return menu_id; }


// Private

