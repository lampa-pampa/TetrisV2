#ifndef INCLUDE_BOARD_IMPL_H
#define INCLUDE_BOARD_IMPL_H

#include "board/board.h"

#include <vector>

#include "brick/brick.h"
#include "cube/cube.h"
#include "vector2/vector2.h"

namespace Tetris
{

class BoardImpl final: public Board
{
public:
    BoardImpl(Vector2 size);

    void put_cubes(const std::vector<Cube>& cubes) override;
    std::vector<int> remove_lines_and_compress(int from_y, int to_y) override;
    bool brick_is_valid(const Brick& brick) const override;
    std::vector<Cube> get_visible_brick_cubes(
        const std::vector<Cube>& cubes) const override;

    CubeMatrix get_cubes() const override
    {
        return cubes_;
    }

private:
    const Vector2 size_;
    CubeMatrix cubes_;

    CubeMatrix create_cubes() const;
    std::vector<int> find_rows_with_line(int from_y, int to_y) const;
    bool is_row_with_line(int y) const;
    Brick try_to_create_line(int y) const;
    void compress(int start_y);

    Cube& get_cube(Vector2 position)
    {
        return cubes_[position.y][position.x];
    }

    const Cube& get_cube(Vector2 position) const
    {
        return cubes_[position.y][position.x];
    }

    void copy_cube_above(Vector2 position)
    {
        const Cube& above{get_cube(position - Vector2{0, 1})};
        get_cube(position).brick_name = above.brick_name;
    }

    bool position_is_valid(Vector2 position) const
    {
        return position_is_in_range(position) and get_cube(position).empty();
    }

    bool position_is_in_range(Vector2 position) const
    {
        return position >= 0 and position < size_;
    }

    void clear_top_row()
    {
        for (auto& cube : cubes_[0])
            cube.clear();
    }
};

} // namespace Tetris

#endif
