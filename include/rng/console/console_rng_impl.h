#ifndef INCLUDE_CONSOLE_RNG_IMPL_H
#define INCLUDE_CONSOLE_RNG_IMPL_H

#include <random>

#include "rng/rng.h"

namespace Tetris
{

class ConsoleRngImpl final: public Rng
{
public:
    ConsoleRngImpl(): rng_{create_rng()} {}

    int random(int range) override
    {
        std::uniform_int_distribution<int> dist(0, range - 1);
        return dist(rng_);
    }

private:
    std::default_random_engine rng_;

    std::default_random_engine create_rng() const
    {
        std::random_device random_device;
        return std::default_random_engine{random_device()};
    }
};

} // namespace Tetris

#endif
