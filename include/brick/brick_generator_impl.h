#ifndef INCLUDE_BRICK_GENERATOR_IMPL_H
#define INCLUDE_BRICK_GENERATOR_IMPL_H

#include "brick/brick_generator.h"

#include "brick/bag.h"
#include "brick/brick.h"
#include "ui/color/color_id_name.h"

namespace Tetris
{

class BrickGeneratorImpl final: public BrickGenerator
{
public:
    BrickGeneratorImpl(
        const Bag<Brick>& bricks, const Bag<Ui::ColorIdName>& color_id_names)
      : bricks_bag_{bricks},
        color_id_names_bag_{color_id_names}
    {}

    Brick generate() override
    {
        return Brick::get_colored(
            bricks_bag_.get_next(), color_id_names_bag_.get_next());
    }

private:
    Bag<Brick> bricks_bag_;
    Bag<Ui::ColorIdName> color_id_names_bag_;
};

} // namespace Tetris

#endif
