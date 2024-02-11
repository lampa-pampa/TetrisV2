#ifndef RNG_IMPL_H
#define RNG_IMPL_H

#include "rng.h"

class RNGImpl: public RNG
{
    public:
        int random(int range) override;
        RNGImpl();
};

#endif