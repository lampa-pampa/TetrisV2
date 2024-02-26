#include "pixel.h"
#include "color.h"
#include "vector_2.h"
#include <ostream>

using std::ostream;

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

std::ostream& operator<<(ostream& os, const Pixel& pixel)
{
    return os << "{" << pixel.coords.x << ", " << pixel.coords.y << ", Color::" << ColorToName.at(pixel.color) << "}";  
}


bool Pixel::empty() const
{
    return this->color == Color::black;
}

void Pixel::clear()
{
    this->color = Color::black;
    this->is_ghost = false;
}