#include "brick_generator_impl.h"
#include "color.h"
#include "brick.h"
#include "bag.h"

BrickGeneratorImpl::BrickGeneratorImpl(Bag<Brick> &&bricks, Bag<Color> &&colors)
:
    bricks_bag(std::move(bricks)),
    colors_bag(std::move(colors))
{}

Brick BrickGeneratorImpl::generate()
{
    return Brick::get_colored(this->bricks_bag.get_next(), this->colors_bag.get_next());
}