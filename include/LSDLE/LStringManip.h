#pragma once

#include <string>
#include <stdexcept>

#include "LNumericLimits.h"

namespace LSDLELIB
{
    std::string get_str_after_char_from_end(std::string str, char c);

    uint8_t string_to_uint8(const std::string& str);

    uint16_t string_to_uint16(const std::string& str);

    int string_to_int32(const std::string& str);

    uint64_t string_to_uint64(const std::string& str);
};
