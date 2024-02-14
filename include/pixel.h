#ifndef PIXEL_H
#define PIXEL_H

#include "color.h"
#include "vector_2.h"

struct Pixel
{
    Vector2 coords;
    Color color;
    bool is_ghost;
    
    Pixel(Vector2 coords, Color color = Color::black, bool is_ghost = false);
    bool operator==(const Pixel &other) const;
    bool empty() const;
    void clear();
};

#endif