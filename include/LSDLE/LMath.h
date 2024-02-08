#pragma once

#include <cmath>

int round_negative_to_zero(int num)
{
    return (num + abs(num)) / 2; 
}