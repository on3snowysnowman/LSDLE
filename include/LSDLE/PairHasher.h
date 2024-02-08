#pragma once

#include <cstdint>


class Uint16PairHash 
{

public:
    std::size_t operator() (const std::pair<uint16_t, uint16_t>& p) const {
        // Compute the hash of the first element shifted by 16 bits
        std::size_t h1 = std::hash<uint16_t>{}(p.first);
        // Compute the hash of the second element
        std::size_t h2 = std::hash<uint16_t>{}(p.second);
        
        // Combine the two hashes in a way that ensures good distribution
        return h1 ^ (h2 << 16);
    }
};