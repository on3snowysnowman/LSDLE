#include "LStringManip.h"


std::string LSDLELIB::get_str_after_char_from_end(std::string str, char c)
{
    int char_found_index = -1;

    for(int i = str.size() - 1; i >= 0; --i)
    {
        if(str.at(i) == c)
        {
            char_found_index = i;
            goto FOUND_CHAR_INDEX;
        }
    }

    // Did not find the index of the char being searched for, simply return
    // the string

    return str;

    // The char has been found, so trim the string so it starts one after
    // the position the char was found
    FOUND_CHAR_INDEX:

    str = str.substr(++char_found_index);

    return str;
}

uint8_t LSDLELIB::string_to_uint8(const std::string& str)
{
    // The number this string represents is negative
    if(str.at(0) == '-') return 0;

    try
    {
        return std::stoi(str);
    }
    catch(const std::out_of_range& e)
    {
        return LSDLELIB::UINT8_LIMIT;
    }
    
}

uint16_t LSDLELIB::string_to_uint16(const std::string& str)
{
    // The number this string represents is negative
    if(str.at(0) == '-') return 0;

    try
    {
        return std::stoi(str);
    } 
    
    catch(const std::out_of_range& e)
    {
        return LSDLELIB::UINT16_LIMIT;
    }
}

int LSDLELIB::string_to_int32(const std::string& str)
{
    try
    {   
        return std::stoi(str);
    } 
    
    catch(const std::out_of_range& e)
    {
        if(str.at(0) == '-') return LSDLELIB::INT32_LIMIT * -1;

        return LSDLELIB::INT32_LIMIT;
    }
}

uint64_t LSDLELIB::string_to_uint64(const std::string& str)
{
    try
    {
        // int num = std::stoi(str);
        // return num;
        
        return std::stoi(str);
    } 
    
    catch(const std::out_of_range& e)
    {
        return LSDLELIB::INT32_LIMIT * (-1 * str.at(0) == '-');
    }
}
