#include "LMath.h"

int LSDLELIB::round_negative_to_zero(int num)
{
    return (num < 0) ? 0 : num;
}

int LSDLELIB::round_num_to_minimum(int num, int minimum)
{
    return (num < minimum) ? minimum : num;
}

int LSDLELIB::round_num_to_maximum(int num, int maximum)
{
    return (num > maximum) ? maximum : num;
}

uint16_t LSDLELIB::handle_uint16_addition(uint16_t a, uint16_t b)
{
    uint16_t budget;
    uint16_t smaller_num = a;
    uint16_t larger_num = b;

    if(a > b)
    {
        smaller_num = b;
        larger_num = a;
    }

    budget = LSDLELIB::UINT16_LIMIT - larger_num;

    if(smaller_num >= budget) return LSDLELIB::UINT16_LIMIT;

    return a + b;
}

int LSDLELIB::handle_int32_addition(int a, int b)
{
    // One of these are negative
    if(a / (b * 1.0) < 0.0) return a + b;

    // else: Either both a and b are negative, or both are positive

    // Convert both to absolute value since the comparison between the 
    // limit will work the same whether they are negative or postiive. 
    // Only the syntax how to calculate the limit will be different, which
    // can be simplified by converting both to absolute value.
    int abs_a = abs(a);
    int abs_b = abs(b);

    if(abs(b) > LSDLELIB::INT32_LIMIT - abs(a)) 
    {
        return (abs_a / a) * LSDLELIB::INT32_LIMIT;
    }

    return a + b;
}

uint16_t LSDLELIB::handle_uint16_subtraction(uint16_t num, 
        uint16_t amount_to_subtract)
{
    if(amount_to_subtract >= num) return 0;

    return num - amount_to_subtract;
}
