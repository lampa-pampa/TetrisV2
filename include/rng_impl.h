#ifndef RNG_IMPL_H
#define RNG_IMPL_H

#include <cstdlib>
#include <ctime>
#include "rng.h"

class RNGImpl final: public RNG
{
    public:
        RNGImpl()
        {
            srand(static_cast<unsigned>(time(NULL)));
        }

        int random(int range) override
        {
            return rand() % range;
        }
};

#endif