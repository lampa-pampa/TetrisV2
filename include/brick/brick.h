#ifndef INCLUDE_BRICK_H
#define INCLUDE_BRICK_H

#include <ostream>
#include <vector>

#include "cube/cube.h"
#include "ui/color/color_id_name.h"
#include "vector_2/vector_2.h"

namespace Tetris
{

std::ostream& operator<<(
    std::ostream& os, const std::vector<Vector2>& cube_positions);

struct Brick final
{
    static constexpr int rotation_count{4};

    std::vector<Vector2> cube_positions;
    Ui::ColorIdName color_id_name;
    Vector2 rotation_offset;

    static Brick get_translated(const Brick& brick, Vector2 position);
    static Vector2 get_rotated_position(
        Vector2 position, Vector2 rotation_offset, int quarters_rotation);
    static Brick get_rotated(const Brick& brick, int quarters_rotation);

    friend inline std::ostream& operator<<(std::ostream& os, const Brick& brick)
    {
        return os << "{{ " << brick.cube_positions << " }, "
                  << brick.rotation_offset << "}";
    }

    static int compute_next_rotation(int rotation, int d_q)
    {
        return (rotation + d_q + rotation_count) % rotation_count;
    }

    static Brick get_transformed(
        const Brick& brick, int quarters_rotation, Vector2 position)
    {
        return get_translated(get_rotated(brick, quarters_rotation), position);
    }

    Brick(std::vector<Vector2> cube_positions = {},
        Ui::ColorIdName color_id_name = Ui::ColorIdName::black,
        Vector2 rotation_offset = {})
      : cube_positions{cube_positions},
        color_id_name{color_id_name},
        rotation_offset{rotation_offset}
    {}

    std::vector<Cube> get_cubes() const;
    int get_min_x() const;
    int get_max_x() const;
    int get_min_y() const;
    int get_max_y() const;
    Vector2 get_size() const;

    bool operator==(const Brick& other) const
    {
        return cube_positions == other.cube_positions
            and rotation_offset == other.rotation_offset;
    }

    bool empty() const
    {
        return cube_positions.empty();
    }
};

} // namespace Tetris

#endif
