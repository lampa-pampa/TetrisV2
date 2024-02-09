#ifndef PIXEL_H
#define PIXEL_H

#include "color.h"
#include "vector_2.h"

struct Pixel
{
    Color color;
    Vector2 coords;
    bool is_ghost;
    Pixel(Color color, Vector2 coords, bool is_ghost = false);
};

#endif