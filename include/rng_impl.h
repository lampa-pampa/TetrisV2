#ifndef Rng_IMPL_H
#define Rng_IMPL_H

#include "rng.h"
#include <cstdlib>
#include <ctime>

class RngImpl final: public Rng
{
public:
    RngImpl()
    {
        std::srand(static_cast<unsigned>(std::time(NULL)));
    }

    int random(int range) override
    {
        return std::rand() % range;
    }
};

#endif