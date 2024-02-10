#include "pixel.h"

Pixel::Pixel(Vector2 coords, Color color, bool is_ghost)
:
    coords(coords),
    color(color),
    is_ghost(is_ghost)
{}