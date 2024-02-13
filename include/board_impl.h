#ifndef BOARD_IMPL_H
#define BOARD_IMPL_H

#include "board.h"
#include "pixel.h"
#include <vector>

class BoardImpl: public Board
{
    int width;
    int height;
    std::vector<std::vector<Pixel>> pixels;

    public:
        BoardImpl(int width, int height);
        std::vector<std::vector<Pixel>> get_pixels() const override;
        int get_width() const override;
};

#endif