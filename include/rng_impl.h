#ifndef RNG_IMPL_H
#define RNG_IMPL_H

#include "rng.h"
#include <cstdlib>
#include <ctime>

class RNGImpl final: public RNG
{
    public:
        RNGImpl()
        {
            std::srand(static_cast<unsigned>(std::time(NULL)));
        }

        int random(int range) override
        {
            return std::rand() % range;
        }
};

#endif