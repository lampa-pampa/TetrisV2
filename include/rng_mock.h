#ifndef INCLUDE_Rng_MOCK_H
#define INCLUDE_Rng_MOCK_H

#include "rng.h"

namespace Tetris
{

class RngMock final: public Rng
{   
public:
    int random(int range) override
    {
        return range - 1;
    }
};

}

#endif