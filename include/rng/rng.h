#ifndef INCLUDE_RNG_H
#define INCLUDE_RNG_H

namespace Tetris
{

class Rng
{
public:
    virtual int random(int range) = 0;
    virtual ~Rng() = default;
};

}

#endif