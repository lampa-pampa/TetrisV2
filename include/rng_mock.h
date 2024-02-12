#ifndef RNG_MOCK_H
#define RNG_MOCK_H

#include "rng.h"

class RNGMock: public RNG
{   
    public:
        int random(int range) override;
};

#endif