#include "pixel.h"
#include "color.h"
#include "vector_2.h"

Pixel::Pixel(Vector2 coords, Color color, bool is_ghost)
:
    coords(coords),
    color(color),
    is_ghost(is_ghost)
{}

Pixel::Pixel(Vector2 coords, Color color)
:
    Pixel(coords, color, false)
{}

Pixel::Pixel(Vector2 coords)
:
    Pixel(coords, Color::black, false)
{}

bool Pixel::operator==(const Pixel &other) const
{
    return this->coords == other.coords
        and this->is_ghost == other.is_ghost
        and this->color == other.color;
}

bool Pixel::empty() const
{
    return (this->is_ghost || this->color == Color::black);
}

void Pixel::clear()
{
    this->color = Color::black;
    this->is_ghost = false;
}