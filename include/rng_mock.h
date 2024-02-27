#ifndef RNG_MOCK_H
#define RNG_MOCK_H

#include "rng.h"

class RNGMock final: public RNG
{   
    public:
        int random(int range) override
        {
            return range - 1;
        }
};

#endif