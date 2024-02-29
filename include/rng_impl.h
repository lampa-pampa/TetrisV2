#ifndef INCLUDE_Rng_IMPL_H
#define INCLUDE_Rng_IMPL_H

#include <cstdlib>
#include <ctime>

#include "rng.h"

namespace Tetris
{

class RngImpl final: public Rng
{
public:
    RngImpl()
    {
        std::srand(std::time(NULL));
    }

    int random(int range) override
    {
        return std::rand() % range;
    }
};

}

#endif