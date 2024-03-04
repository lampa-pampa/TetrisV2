#ifndef INCLUDE_BRICK_GENERATOR_IMPL_H
#define INCLUDE_BRICK_GENERATOR_IMPL_H

#include "bag.h"
#include "brick_generator.h"
#include "brick.h"

namespace Tetris
{

class BrickGeneratorImpl final: public BrickGenerator
{
    Bag<Brick> bricks_bag;
    Bag<int> color_codes_bag;

public:
    BrickGeneratorImpl(const Bag<Brick>& bricks, const Bag<int>& color_codes)
    :
        bricks_bag{bricks},
        color_codes_bag{color_codes}
    {}
    
    Brick generate() override
    {
        return Brick::get_colored(
            this->bricks_bag.get_next(), this->color_codes_bag.get_next());
    }
};

}

#endif