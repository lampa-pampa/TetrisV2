#ifndef BRICK_H
#define BRICK_H

#include "pixel.h"
#include "vector_2.h"
#include <vector>

struct Brick
{
    std::vector<Pixel> pixels;
    Vector2 coords;
};

#endif