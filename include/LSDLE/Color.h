#pragma once

#include <cstdint>
#include <string>

class Color
{

public:

    Color(uint8_t _r, uint8_t _g, uint8_t _b, std::string name)
    {   
        r = _r;
        g = _g;
        b = _b;
    }

    uint8_t r;
    uint8_t g;
    uint8_t b;

    std::string name;

};
