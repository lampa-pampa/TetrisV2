#ifndef RNG_IMPL_H
#define RNG_IMPL_H

#include "rng.h"

class RNGImpl final: public RNG
{
    public:
        int random(int range) override;
        RNGImpl();
};

#endif