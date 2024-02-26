#ifndef PIXEL_H
#define PIXEL_H

#include "color.h"
#include "vector_2.h"
#include <ostream>

struct Pixel
{
    Vector2 coords;
    Color color;
    bool is_ghost;
    
    Pixel(Vector2 coords, Color color, bool is_ghost);
    Pixel(Vector2 coords, Color color);
    Pixel(Vector2 coords);
    bool operator==(const Pixel &other) const;
    friend std::ostream& operator<<(std::ostream& os, const Pixel& pixel);

    bool empty() const;
    void clear();
};

#endif