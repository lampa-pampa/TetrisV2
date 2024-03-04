#ifndef INCLUDE_BOARD_H
#define INCLUDE_BOARD_H

#include <vector>

#include "brick.h"
#include "cube.h"

namespace Tetris
{

class Board
{
    using CubeMatrix = std::vector<std::vector<Cube>>;

public:
    virtual bool brick_is_valid(const Brick& brick) const = 0;
    virtual void put_cubes(const std::vector<Cube>& cubes) = 0;
    virtual void clear_cubes(const std::vector<Cube>& cubes) = 0;
    virtual int remove_lines_and_compress(int from_y, int to_y) = 0;
    virtual int get_width() const = 0;
    virtual const CubeMatrix& get_cubes() const = 0;
    virtual CubeMatrix get_cubes(int offset) const = 0;
    virtual ~Board() = default;
};

}

#endif