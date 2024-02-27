#ifndef BRICK_GENERATOR_IMPL_H
#define BRICK_GENERATOR_IMPL_H

#include "bag.h"
#include "brick.h"
#include "brick_generator.h"
#include "color.h"

class BrickGeneratorImpl final: public BrickGenerator
{
    Bag<Brick> bricks_bag;
    Bag<Color> colors_bag;

    public:
        BrickGeneratorImpl(const Bag<Brick> &bricks, const Bag<Color> &colors);
        Brick generate() override;
};

#endif