#ifndef INCLUDE_BOARD_MOCK_H
#define INCLUDE_BOARD_MOCK_H

#include "board/board.h"

#include <vector>

#include "brick/brick.h"
#include "cube/cube.h"
#include "vector2/vector2.h"

namespace Tetris
{

class BoardMock final: public Board
{
public:
    void put_cubes(const std::vector<Cube>& cubes) override {}
    std::vector<int> remove_lines_and_compress(int from_y, int to_y) override {}
    bool brick_is_valid(const Brick& brick) const override {}
    std::vector<Cube> get_visible_brick_cubes(
        const std::vector<Cube>& cubes) const override {}

    CubeMatrix get_cubes() const override {}
};

} // namespace Tetris

#endif
