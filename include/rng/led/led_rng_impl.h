#ifndef INCLUDE_LED_RNG_IMPL_H
#define INCLUDE_LED_RNG_IMPL_H

#include "rng/rng.h"

#include <Arduino.h>

namespace Tetris
{

class LedRngImpl final: public Rng
{
public:
    LedRngImpl(int unused_pin)
    {
        randomSeed(analogRead(unused_pin));
    }

    int random(int range) override
    {
        return ::random(range);
    }
};

} // namespace Tetris

#endif
