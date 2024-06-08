#ifndef INCLUDE_CUBE_H
#define INCLUDE_CUBE_H

#include <ostream>

#include "ui/color/color_id_name.h"
#include "vector_2/vector_2.h"

namespace Tetris
{

struct Cube final
{
    constexpr static Ui::ColorIdName empty_color_id_name{
        Ui::ColorIdName::black};

    Vector2 position;
    Ui::ColorIdName color_id_name;

    friend std::ostream& operator<<(std::ostream& os, const Cube& cube)
    {
        return os << "{" << cube.position.x << ", " << cube.position.y << ", "
                  << cube.color_id_name << "}";
    }

    Cube(int x, int y, Ui::ColorIdName color_id_name = empty_color_id_name)
      : position{x, y},
        color_id_name{color_id_name}
    {}

    bool operator==(const Cube& other) const
    {
        return position == other.position
            and color_id_name == other.color_id_name;
    }

    void clear()
    {
        color_id_name = empty_color_id_name;
    }

    bool empty() const
    {
        return color_id_name == empty_color_id_name;
    }
};

} // namespace Tetris

#endif
