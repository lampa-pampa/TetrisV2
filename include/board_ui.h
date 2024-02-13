#ifndef BOARD_UI_H
#define BOARD_UI_H

#include "pixel.h"
#include <vector>

class BoardUI
{
    public:
        virtual void refresh_board(std::vector<std::vector<Pixel>> &pixels);
        virtual ~BoardUI() = default;
};

#endif