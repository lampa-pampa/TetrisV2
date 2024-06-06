#ifndef UI_RENDER_CUBES_H
#define UI_RENDER_CUBES_H

#include <cstdint>
#include <vector>

#include "cube/cube.h"
#include "ui/render/sprite.h"
#include "vector_2/vector_2.h"

namespace Tetris::Ui
{

class RenderCubes final
{
public:
    constexpr RenderCubes(Vector2 position, int cube_size = 3)
      : position_{position},
        cube_size_{cube_size}
    {}

    Sprites render(
        const std::vector<Cube>& cubes, uint_fast8_t color_value = 0xff) const;

private:
    const Vector2 position_;
    const int cube_size_;
};

} // namespace Tetris::Ui

#endif
