#include "rng_mock.h"

int RNGMock::random(int range)
{
    return range - 1;
}