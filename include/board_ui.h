#ifndef BOARD_UI
#define BOARD_UI

#include "pixel.h"
#include <vector>

class BoardUI
{
    public:
        virtual void refresh_board(std::vector<std::vector<Pixel>> pixels);
        virtual ~BoardUI() = default;
};

#endif