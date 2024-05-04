#ifndef INCLUDE_BOARD_IMPL_H
#define INCLUDE_BOARD_IMPL_H

#include "board/board.h"

#include <vector>

#include "brick/brick.h"
#include "cube/cube.h"
#include "vector_2/vector_2.h"

namespace Tetris
{

class BoardImpl final: public Board
{
public:
    BoardImpl(Vector2 size, int offset = 0);
    
    void put_cubes(const std::vector<Cube>& cubes) override;
    std::vector<int> remove_lines_and_compress(int from_y, int to_y) override;
    bool brick_is_valid(const Brick& brick) const override;
    std::vector<Cube> get_visible_brick_cubes(
        const std::vector<Cube>& cubes) const override;

    int get_offset() const override
    {
        return offset_;
    }

    CubeMatrix get_visible_cubes() const override
    {
        return {cubes_.begin() + offset_, cubes_.end()};
    }

    CubeMatrix get_cubes() const
    {
        return cubes_;
    }

private:
    const Vector2 size_;
    const int offset_;
    CubeMatrix cubes_;
    
    CubeMatrix create_cubes() const;
    std::vector<int> find_rows_with_line(int from_y, int to_y) const;
    bool is_row_with_line(int y) const;
    Brick try_to_create_line(int y) const;
    void compress(int start_y);

    std::vector<Cube>& get_row(int y)
    {
        return cubes_[y + offset_];
    }

    const std::vector<Cube>& get_row(int y) const
    {
        return cubes_[y + offset_];
    }
    
    Cube& get_cube(Vector2 position)
    {
        return get_row(position.y)[position.x];
    }

    const Cube& get_cube(Vector2 position) const
    {
        return get_row(position.y)[position.x];
    }

    void copy_cube_above(Vector2 position)
    {
        const Cube& above{get_cube(position - Vector2{0, 1})};
        get_cube(position).color_id = above.color_id;
    }

    bool position_is_valid(Vector2 position) const
    {
        return position_is_in_range(position)
            and get_cube(position).empty();
    }

    bool position_is_in_range(Vector2 position) const
    {
        return position.x >= 0 and position.x < size_.x
            and position.y >= -offset_ and position.y < size_.y;
    }

    void clear_top_row()
    {
        for (auto& cube : get_row(-offset_))
            cube.clear();
    }
};

}

#endif