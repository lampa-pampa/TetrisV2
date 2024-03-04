#include "matrix_display_game_ui_impl.h"

#include <string>
#include <vector>

#include <boost/range/irange.hpp>
#include <ncurses.h>

#include "brick.h"
#include "color_name.h"
#include "matrix.h"
#include "vector_2.h"

namespace Tetris
{

using boost::irange;
using std::string;
using std::vector;

void MatrixDisplayGameUiImpl::draw_border()
{
    const int display_width{this->matrix.get_width()};
    const int display_height{this->matrix.get_height()};

    this->draw_rectangle(
        {0, 0},
        display_width,
        border_width,
        border_color
    );
    this->draw_rectangle(
        {0, 0},
        border_width,
        display_height,
        border_color
    );
    this->draw_rectangle(
        {display_width - border_width, 0},
        border_width,
        display_height,
        border_color
    );
    this->draw_rectangle(
        {0, display_height - border_width},
        display_width,
        border_width,
        border_color
    );

    this->draw_rectangle(
        {center_x, 0},
        border_width,
        display_height,
        border_color
    );

    this->draw_rectangle(
        {center_x, next_brick_position.y + (max_brick_height - 1) * cube_size},
        display_width - center_x,
        border_width,
        border_color
    );

    this->draw_rectangle(
        {center_x, hold_brick_position.y + (max_brick_height - 1) * cube_size},
        display_width - center_x,
        border_width,
        border_color
    );

    this->matrix.refresh(this->color_codes);
}

void MatrixDisplayGameUiImpl::draw_rectangle(
    Vector2 position,
    int width,
    int height,
    ColorName color
){
    const int color_code{color_name_to_code.at(color)};
    for (const auto& y : irange(position.y, position.y + height))
    {
        for (const auto& x : irange(position.x, position.x + width))
            this->draw_pixel({x, y}, color_code);
    }
}

void MatrixDisplayGameUiImpl::draw_cube(Vector2 position, int color_code)
{
    for (const auto& y : irange(position.y, position.y + cube_size))
    {
        for (const auto& x : irange(position.x, position.x + cube_size))
            this->draw_pixel({x, y}, color_code);
    }
}

void MatrixDisplayGameUiImpl::draw_board(Vector2 position, const CubeMatrix& board)
{
    for (const auto& y : irange<int>(board.size()))
    {
        const int cube_y{position.y + y * cube_size};
        for (const auto& x : irange<int>(board[y].size()))
        {
            const int cube_x{position.x + x * cube_size};
            const int color_code{board[y][x].color_code};
            this->draw_cube({cube_x, cube_y}, color_code);
        }
    }
}

void MatrixDisplayGameUiImpl::draw_brick(Vector2 position, vector<Cube> cubes)
{
    for (const auto& cube : cubes)
    {
        const int cube_x{position.x + cube.position.x * cube_size};
        const int cube_y{position.y + cube.position.y * cube_size};
        const int color_code{cube.color_code};
        this->draw_cube({cube_x, cube_y}, color_code);
    }
}

void MatrixDisplayGameUiImpl::cover_brick_with_rectangle(Vector2 position)
{
    const Vector2 rectangle_position{
        position.x - (max_brick_width - 1) / 2 * cube_size,
        position.y - (max_brick_height - 1) / 2 * cube_size
    };
    const int width{max_brick_width * cube_size};
    const int height{max_brick_height * cube_size};
    this->draw_rectangle(rectangle_position, width, height, ColorName::black);
}

MatrixDisplayGameUiImpl::MatrixDisplayGameUiImpl(MatrixDisplay& matrix)
:
    matrix{matrix}
{
    this->color_codes.resize(
        this->matrix.get_height(),
        vector<int>(this->matrix.get_width())
    );
    this->draw_border();
}

void MatrixDisplayGameUiImpl::draw_board(const CubeMatrix& cubes)
{
    this->board_cubes = cubes;
    this->draw_board(board_position, cubes);
    this->matrix.refresh(this->color_codes);
}

void MatrixDisplayGameUiImpl::draw_next(const Brick& brick)
{
    this->next_brick = brick;
    this->cover_brick_with_rectangle(next_brick_position);
    this->draw_brick(next_brick_position, brick.cubes);
    this->matrix.refresh(this->color_codes);
}

void MatrixDisplayGameUiImpl::draw_hold(const Brick& brick)
{
    this->hold_brick = brick;
    this->cover_brick_with_rectangle(hold_brick_position);
    this->draw_brick(hold_brick_position, brick.cubes);
    this->matrix.refresh(this->color_codes);
}

void MatrixDisplayGameUiImpl::draw_score(unsigned long long score)
{

}

void MatrixDisplayGameUiImpl::draw_tetrises(unsigned long long tetrises)
{

}

void MatrixDisplayGameUiImpl::input_received(int input)
{
    if (const auto it{this->input_to_signal.find(input)};
        it != this->input_to_signal.end()
    )
        it->second();
}

}