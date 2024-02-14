#ifndef BOARD_IMPL_H
#define BOARD_IMPL_H

#include "board.h"
#include "pixel.h"
#include "vector_2.h"
#include <vector>

class BoardImpl: public Board
{
    int width;
    int height;
    std::vector<std::vector<Pixel>> pixels;
    bool position_is_in_range(Vector2 position) const;

    public:
        BoardImpl(int width, int height);
        const std::vector<std::vector<Pixel>>& get_pixels() const override;
        int get_width() const override;
        bool is_space_for_brick(const Brick &brick) const override;
        void add_brick(const Brick &brick) override;
        void remove_brick(const Brick &brick) override;
};

#endif