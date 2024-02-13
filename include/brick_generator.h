#ifndef BRICK_GENERATOR_H
#define BRICK_GENERATOR_H

#include "brick.h"

class BrickGenerator
{
    public:
        virtual Brick generate() = 0;
        virtual ~BrickGenerator() = default;
};

#endif