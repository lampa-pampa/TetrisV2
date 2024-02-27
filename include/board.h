#ifndef BOARD_H
#define BOARD_H

#include "brick.h"
#include "pixel.h"
#include <vector>

class Board
{
    public:
        virtual const std::vector<std::vector<Pixel>>& get_pixels() const = 0; 
        virtual int get_width() const = 0;
        virtual bool is_space_for_brick(const Brick& brick) const = 0;
        virtual void add_brick(const Brick& brick) = 0;
        virtual void remove_brick(const Brick& brick) = 0;
        virtual int remove_lines_in_range_and_compress(int from_y, int to_y) = 0;
        virtual ~Board() = default;
};

#endif