#include "pixel.h"

Pixel::Pixel(Color color, Vector2 coords, bool is_ghost)
:
    color(color),
    coords(coords),
    is_ghost(is_ghost)
{}