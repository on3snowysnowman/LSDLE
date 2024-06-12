#pragma once

#include "LNumericLimits.h"

#include <cmath>
#include <cstdint>
#include <iostream>

namespace LSDLELIB
{
    int round_negative_to_zero(int num);

    int round_num_to_minimum(int num, int minimum);

    int round_num_to_maximum(int num, int maximum);

    uint16_t handle_uint16_addition(uint16_t a, uint16_t b);

    int handle_int32_addition(int a, int b);

    uint16_t handle_uint16_subtraction(uint16_t num, 
        uint16_t amount_to_subtract);
}

