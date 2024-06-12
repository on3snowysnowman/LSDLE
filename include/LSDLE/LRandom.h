#pragma once

#include <random>


class LRandomGenerator {

public:
    
    static int get_random_num(int lower, int higher) 
    {
        std::uniform_int_distribution<int> distribution(lower, higher);
        return distribution(gen);
    }

private:
    static std::mt19937 gen;
};
