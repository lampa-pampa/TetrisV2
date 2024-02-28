#ifndef Rng_MOCK_H
#define Rng_MOCK_H

#include "rng.h"

class RngMock final: public Rng
{   
public:
    int random(int range) override
    {
        return range - 1;
    }
};

#endif