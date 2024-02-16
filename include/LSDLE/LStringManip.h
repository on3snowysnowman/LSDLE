#pragma once

#include <string>

namespace LStringManip
{

    static std::string get_str_after_char(std::string str, char c)
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
};
