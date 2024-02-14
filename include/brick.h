#ifndef BRICK_H
#define BRICK_H

#include "pixel.h"
#include "vector_2.h"
#include <vector>

struct Brick
{
    static Brick get_colored(const Brick &brick, Color color);
    static Brick get_translated(const Brick &brick, Vector2 position);
    static Brick get_rotated(const Brick &brick, int quarters_rotation);
    static Brick get_transformed(const Brick &brick, int quarters_rotation, Vector2 position);
    static Brick get_ghostified(const Brick &brick);

    std::vector<Pixel> pixels;
    bool is_center_moved;
    
    Brick(std::vector<Pixel> pixels, bool is_center_moved);
    Brick(std::vector<Pixel> pixels);
    Brick();
    int get_min_x() const;
    int get_max_x() const;
    int get_min_y() const;
    int get_max_y() const;
    bool operator==(const Brick &other) const;
};

#endif