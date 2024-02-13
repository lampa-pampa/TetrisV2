#include "brick_generator_impl.h"
#include "pixel.h"
#include "color.h"
#include "brick.h"
#include "bag.h"

BrickGeneratorImpl::BrickGeneratorImpl(Bag<Brick> &&bricks, Bag<Color> &&colors)
:
    bricks_bag(std::move(bricks)),
    colors_bag(std::move(colors))
{}

Brick BrickGeneratorImpl::get_colored_brick(const Brick &brick, Color color)
{
    Brick colored_brick{brick};
    for(Pixel &pixel : colored_brick.pixels)
        pixel.color = color;
    return colored_brick;
}

Brick BrickGeneratorImpl::generate()
{
    return get_colored_brick(this->bricks_bag.get_next(), this->colors_bag.get_next());
}