#pragma once

#include <cstdint>

#include "MenuToolItem.h"
#include "../ConsoleOutputHandler.h"
#include "../InputHandler.h"
#include "Window.h"


/**
 * @brief A MenuToolItem, used in the MenuTools' menu simulation.
 * 
 * The MenuToolVariable is an editable variable that the user may modify. Only
 * the contents of the variable can be modified by the user, not the name. The 
 * Variable comes in three different types : STRING, INT and FLOAT. If the 
 * Variable is of STRING type, any character may be added to the content. If 
 * the Variable is of INT type, only numbers may be added, with no decimal 
 * point. Lastly, if it is of FLOAT type, only number may be added, and a 
 * decimal may be placed in the content to resemble a floating point.
 */
class MenuToolVariable : public MenuToolItem
{

public:

    MenuToolVariable();
    MenuToolVariable(Window* window, StringType _str_type, 
        std::string _cursor_color, std::string _name,
        std::string _content = "", std::string default_content = "");

    void start() final;

    void reset() final;

    /**
     * @brief Render the Variable with the understanding that it has no status
     * (it is not hovered or selected)
     */
    void render_no_status() const final;

    /**
     * @brief Render the Variable with the understanding it is hovered by the 
     * cursor.
     */
    void render_hovered() const final;

    /**
     * @brief Render the Variable with the understanding it is selected
     */
    void render_selected() const final;
    
    /**
     * @brief Handles the input from the user while selected. This includes 
     * the modification of the variable's contents.
     * 
     * @return Status 
     */
    Status handle_input() final;

    /**
     * @brief Converts the content to a uint16 and returns it. Any trunkation of the content
     * is handled.
     */
    uint16_t fetch_uint16();
    
    // Content of the variable 
    std::string content;


private:


    // Members

    using input_handling_function = 
        MenuToolItem::Status (MenuToolVariable::*)();

    /**
     * @brief This function pointer is to the class function that will handle
     * the input from the user, depending on the type of the Variable. Since 
     * input handling is different for each Variable type, this exists to remove
     * the extra computation of an if statement to check what type the Variable
     * is each frame input needs to be handled, and instead a pointer to the 
     * respective input handling function is set on creation of the Variable, 
     * depending on what type of Variable is created.
     */
    input_handling_function targ_input_handling_function;

    /**
     * If the content contains a decimal point to track float values. This 
     * boolean is only important if the StringType is a Float. Otherwise, it is
     * ignored.
     */
    bool has_decimal_point = false;

    // Type of the string
    StringType str_type = STRING;

    // Name of the variable
    std::string name;

    // What the content of this variable will be set to if left empty
    std::string default_content;


    // Methods

    /**
     * @brief Called once during construction. Initializes and checks the initial contents 
     * depending on the specified StringType of the Variable. Such checks include checking 
     * if the type is an int or float and has letters in it, or if the type is a float if it
     * has more than one decimal point.
     */
    void handle_init_string_type();

    /**
     * For StringType of INT or FLOAT only. Removes any trailing zeros in front of the numbers
     * for INT type, or the zero before the decimal point for FLOAT type.
     */
    void remove_first_zeros();

    /**
     * @brief Specific function for handling input from the user if the 
     * Variable type is FLOAT
     */
    Status handle_float_input();

    /**
     * @brief Specific function for handling input from the user if the 
     * Variable type is INT
     */
    Status handle_int_input();

    /**
     * @brief Specific function for handling input from the user if the 
     * Variable type is STRING
     */
    Status handle_string_input();
};
