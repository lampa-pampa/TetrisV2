#ifndef INCLUDE_BOARD_IMPL_H
#define INCLUDE_BOARD_IMPL_H

#include <vector>

#include "board.h"
#include "brick.h"
#include "pixel.h"
#include "vector_2.h"

namespace Tetris
{

class BoardImpl final: public Board
{
    using Pixels = std::vector<std::vector<Pixel>>;

    const int width;
    const int height;
    Pixels pixels;
    
    std::vector<Brick> find_lines_in_range(int from_y, int to_y) const;
    void compress(int start_y);
    
    bool position_is_in_range(Vector2 position) const
    {
        return position.x >= 0 and position.x < this->width
            and position.y >= 0 and position.y < this->height;
    }

public:
    BoardImpl(int width, int height);

    bool is_space_for_brick(const Brick& brick) const override;
    void put_pixels(const std::vector<Pixel>& pixels) override;
    void clear_pixels(const std::vector<Pixel>& pixels) override;
    int remove_lines_in_range_and_compress(int from_y, int to_y) override;
    
    int get_width() const override
    {
        return this->width;
    }

    const Pixels& get_pixels() const override
    {
        return this->pixels;
    }
};

}

#endif