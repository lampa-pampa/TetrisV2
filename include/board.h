#ifndef BOARD_H
#define BOARD_H

#include "pixel.h"
#include <vector>

class Board
{
    public:
        virtual std::vector<std::vector<Pixel>> get_pixels() const = 0; 
        virtual int get_width() const = 0;
        virtual ~Board() = default;
};

#endif