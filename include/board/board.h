#ifndef INCLUDE_BOARD_H
#define INCLUDE_BOARD_H

#include <vector>

#include "brick/brick.h"
#include "cube/cube.h"

namespace Tetris
{

class Board
{
public:
    using CubeMatrix = std::vector<std::vector<Cube>>;

    virtual void put_cubes(const std::vector<Cube>& cubes) = 0;
    virtual std::vector<int> remove_lines_and_compress(
        int from_y, int to_y) = 0;
    virtual bool brick_is_valid(const Brick& brick) const = 0;
    virtual int get_offset() const = 0;
    virtual CubeMatrix get_visible_cubes() const = 0;
    virtual std::vector<Cube> get_visible_brick_cubes(
        const std::vector<Cube>& cubes) const = 0;
    virtual ~Board() = default;
};

} // namespace Tetris

#endif
