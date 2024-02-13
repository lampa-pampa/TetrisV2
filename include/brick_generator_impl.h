#ifndef BRICK_GENERATOR_IMPL_H
#define BRICK_GENERATOR_IMPL_H

#include "bag.h"
#include "brick.h"
#include "brick_generator.h"
#include "color.h"

class BrickGeneratorImpl: public BrickGenerator
{
    Bag<Brick> bricks_bag;
    Bag<Color> colors_bag;

    public:
        BrickGeneratorImpl(Bag<Brick> &&bricks, Bag<Color> &&colors);
        Brick generate() override;
};

#endif