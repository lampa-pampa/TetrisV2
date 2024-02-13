#ifndef BOARD_IMPL_H
#define BOARD_IMPL_H

#include "board.h"
#include "board_ui.h"
#include "pixel.h"
#include <memory>
#include <vector>

class BoardImpl: public Board
{
    std::shared_ptr<BoardUI> ui;
    int width;
    int height;
    std::vector<std::vector<Pixel>> pixels;

    public:
        BoardImpl(std::unique_ptr<BoardUI> &&ui, int width, int height);
        std::vector<std::vector<Pixel>> get_pixels() const;
        int get_width() const override;
};

#endif