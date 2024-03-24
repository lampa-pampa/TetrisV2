#ifndef INCLUDE_BRICK_GENERATOR_IMPL_H
#define INCLUDE_BRICK_GENERATOR_IMPL_H

#include "brick_generator.h"

#include "bag.h"
#include "brick.h"

namespace Tetris
{
    
class BrickGeneratorImpl final: public BrickGenerator
{
public:
    BrickGeneratorImpl(
        const Bag<Brick>& bricks, const Bag<uint_fast8_t>& color_ids)
    :
        bricks_bag_{bricks},
        color_ids_bag_{color_ids}
    {}
    
    Brick generate() override
    {
        return Brick::get_colored(
            bricks_bag_.get_next(), color_ids_bag_.get_next());
    }

private:
    Bag<Brick> bricks_bag_;
    Bag<uint_fast8_t> color_ids_bag_;
};

}

#endif