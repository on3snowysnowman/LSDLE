#pragma once

#include "LNumericLimits.h"

#include <cmath>
#include <cstdint>

namespace LMath
{
    int round_negative_to_zero(int num)
    {
        return (num < 0) ? 0 : num;
    }

    int round_num_to_maximum(int num, int maximum)
    {
        return (num > maximum) ? maximum : num;
    }

    uint16_t handle_uint16_addition(uint16_t a, uint16_t b)
    {
        uint16_t budget;
        uint16_t smaller_num = a;
        uint16_t larger_num = b;

        if(a > b)
        {
            smaller_num = b;
            larger_num = a;
        }

        budget = LNumericLimits::UINT16_LIMIT - larger_num;

        if(smaller_num >= budget) return LNumericLimits::UINT16_LIMIT;

        return a + b;
    }

    uint16_t handle_uint16_subtraction(uint16_t num, 
        uint16_t amount_to_subtract)
    {
        if(amount_to_subtract >= num) return 0;

        return num - amount_to_subtract;
    }
}

