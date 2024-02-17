#include "brick_generator_impl.h"
#include "color.h"
#include "brick.h"
#include "bag.h"

BrickGeneratorImpl::BrickGeneratorImpl(const Bag<Brick> &bricks, const Bag<Color> &colors)
:
    bricks_bag(bricks),
    colors_bag(colors)
{}

Brick BrickGeneratorImpl::generate()
{
    return Brick::get_colored(this->bricks_bag.get_next(), this->colors_bag.get_next());
}