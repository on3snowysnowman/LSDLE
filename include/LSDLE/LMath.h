#pragma once

#include <cmath>

int round_negative_to_zero(int num)
{
    return (num < 0) ? 0 : num;
}

int round_num_to_maximum(int num, int maximum)
{
    return (num > maximum) ? maximum : num;
}