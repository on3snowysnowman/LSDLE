#include "MenuHandler.h"


// Constructors / Deconstructor

MenuHandler::MenuHandler() {}


// Public

void MenuHandler::update()
{
    for(Menu* m : active_menus)
    {
        m->update();
    }

    while(!instruction_queue.empty())
    {
        InstructionSequence& i = instruction_queue.front();
        instruction_queue.pop();

        process_instruction(i);
    }
}

void MenuHandler::register_menu(Menu* m) 
{
    m->set_instruction_queue(&instruction_queue);
    registered_menus[m->get_id()] = m;
}

void MenuHandler::activate_menu(std::string menu_id)
{
    activate_menu(registered_menus.at(menu_id));
}

void MenuHandler::activate_menu(Menu* m)
{
    if(m->is_activated()) return;

    active_menus.push_front(m);
    m->flag_activated();
    m->start();
}

void MenuHandler::deactivate_menu(std::string menu_id)
{
    deactivate_menu(registered_menus.at(menu_id));
}

void MenuHandler::deactivate_menu(Menu* m)
{
    if(!m->is_activated()) return; 

    for(std::list<Menu*>::iterator it = active_menus.begin();
        it != active_menus.end(); ++it)
    {
        if(m == *it)
        {
            m->flag_deactivated();
            active_menus.erase(it);
            return;
        }
    }
}


// Private

void MenuHandler::process_instruction(InstructionSequence& i)
{
    std::string instruction = get_next_instruction(i);

    if(instruction == "activate_menu")
    {
        instruction = get_next_instruction(i);

        activate_menu(instruction);
    }

    else if(instruction == "deactivate_menu")
    {
        instruction = get_next_instruction(i);

        deactivate_menu(instruction);
    }
}

std::string MenuHandler::get_next_instruction(InstructionSequence& i) const
{
    std::string instruction = i.instructions.front();
    i.instructions.pop();

    return instruction;
}
