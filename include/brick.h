#ifndef BRICK_H
#define BRICK_H

#include "pixel.h"
#include <vector>

struct Brick
{
    static Brick get_colored(const Brick &brick, Color color);
    
    std::vector<Pixel> pixels;
    bool is_center_moved;
    int get_min_x() const;
    int get_max_x() const;
    int get_min_y() const;
    int get_max_y() const;
    bool operator==(const Brick &other) const;
};

#endif