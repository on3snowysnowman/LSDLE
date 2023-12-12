#pragma once

#include <string>


/**
 * @brief A basic data container for a String that has a color applied to it
 * 
 */
class ColorString
{

public:

    ColorString() {}
    ColorString(std::string _content, std::string _color)
    {
        content = _content;
        color = _color;
    }

    std::string content; // The string content itself
    
    std::string color; // Color of the string
};
