#ifndef BRICK_GENERATOR_H
#define BRICK_GENERATOR_H

#include "brick.h"
#include "color.h"

class BrickGenerator
{
    public:
        virtual Brick get_colored_brick(const Brick &brick, Color color) = 0;
        virtual Brick generate() = 0;
        virtual ~BrickGenerator() = default;
};

#endif