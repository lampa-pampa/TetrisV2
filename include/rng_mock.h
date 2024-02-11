#ifndef RNG_MOCK_H
#define RNG_MOCK_H

#include "rng.h"
#include <vector>

class RNGMock: public RNG
{
    const std::vector<int> numbers;
    int current_index;
    public:
        int random(int range) override;
        RNGMock(std::vector<int> numbers);
};

#endif