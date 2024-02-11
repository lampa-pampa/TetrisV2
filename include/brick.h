#ifndef BRICK_H
#define BRICK_H

#include "pixel.h"
#include "vector_2.h"
#include <vector>

struct Brick
{
    std::vector<Pixel> pixels;
    Vector2 coords;
    bool is_center_moved;
    int get_min_x() const;
    int get_max_x() const;
    int get_min_y() const;
    int get_max_y() const;
};

#endif