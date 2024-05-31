#ifndef INCLUDE_BRICK_GENERATOR_H
#define INCLUDE_BRICK_GENERATOR_H

#include "brick/brick.h"

namespace Tetris
{

class BrickGenerator
{
public:
    virtual Brick generate() = 0;
    virtual ~BrickGenerator() = default;
};

} // namespace Tetris

#endif
