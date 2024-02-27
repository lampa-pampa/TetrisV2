#ifndef PIXEL_H
#define PIXEL_H

#include "color.h"
#include "vector_2.h"
#include <ostream>

struct Pixel final
{
    Vector2 coords;
    Color color;
    bool is_ghost;
    
    Pixel(int x, int y, Color color, bool is_ghost);
    Pixel(int x, int y, Color color);
    Pixel(int x, int y);
    bool operator==(const Pixel &other) const;
    friend std::ostream& operator<<(std::ostream& os, const Pixel& pixel);

    bool empty() const;
    void clear();
};

#endif