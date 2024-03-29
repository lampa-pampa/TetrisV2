#include <ncurses.h>

#include "board_impl.h"
#include "brick_generator_impl.h"
#include "config.h"
#include "console_game_controller_impl.h"
#include "game_impl.h"
#include "rng_impl.h"
#include "score_counter_impl.h"
#include "timer_impl.h"
#include "ui/color_id_name.h"
#include "ui/console_matrix_display_impl.h"
#include "ui/matrix_display_game_ui_impl.h"

using Tetris::BoardImpl;
using Tetris::BrickGeneratorImpl;
using Tetris::Config;
using Tetris::ConsoleGameControllerImpl;
using Tetris::GameImpl;
using Tetris::RngImpl;
using Tetris::ScoreCounterImpl;
using Tetris::TimerImpl;
using Tetris::Ui::ColorIdName;
using Tetris::Ui::ConsoleMatrixDisplayImpl;
using Tetris::Ui::get_color_id;
using Tetris::Ui::MatrixDisplayGameUiImpl;

int main()
{
    Config config{
        {
            {
                {64, 64},
                {2, 1},
                0xff,
            },
            {
                KEY_LEFT,
                KEY_RIGHT,
                KEY_UP,
                KEY_DOWN,
                ' ',
                'x',
                'z',
                'c',
            },
            {
                {
                    {{2, 2}, {14, 8}},
                    {{48, 2}, {14, 8}},
                    {{2, 12}, {13, 41}},
                    {{2, 55}, {13, 7}},
                    {{17, 2}, {30, 60}},
                    {{49, 12}, {13, 7}},
                    {{49, 20}, {13, 19}},
                    {{49, 41}, {13, 7}},
                    {{49, 49}, {13, 13}},
                },
                {
                    {{{2, 12}, {13, 41}}},
                    {{{2, 55}, {13, 7}}, 3},
                    {{{17, 2}, {30, 60}}},
                    {{{49, 12}, {13, 7}}},
                    {{{49, 20}, {13, 19}}, 9},
                    {{{49, 41}, {13, 7}}},
                    {{{49, 49}, {13, 13}}, 6},
                },
                {
                    "PAUSED",
                    "GAME\nOVER",
                    "L\nE\nV\nE\nL",
                    "SCO",
                    "TET",
                },
                {
                    {{3, 13}, {11, 3}, 10, 1},
                },
            },
            {
                {
                    {get_color_id(ColorIdName::black)},
                    {get_color_id(ColorIdName::white)},
                    {get_color_id(ColorIdName::sunset_orange)},
                    {
                        {get_color_id(ColorIdName::sunset_orange)},
                        {get_color_id(ColorIdName::sunset_orange)},
                        {
                            {get_color_id(ColorIdName::islamic_green)},
                            {get_color_id(ColorIdName::davy_s_grey)},
                        },
                    },
                    {
                        {get_color_id(ColorIdName::sunset_orange)},
                        {get_color_id(ColorIdName::sunset_orange)},
                    },
                    {
                        {get_color_id(ColorIdName::sunset_orange)},
                        {get_color_id(ColorIdName::sunset_orange)},
                    },
                },
                {
                    0xff,
                    {
                        0xff,
                        0xff,
                        0xff,
                        80,
                    },
                },
            },
            3
        },
        {
            {{10, 20}, 2},
            {
                100000,
                2,
                1,
            },
            {
                {{ {-1, 0}, {0, 0}, {1, 0}, {2, 0} }, {1, 0} },
                {{ {0, -1}, {1, -1}, {0, 0}, {1, 0} }, {0, -1} },
                {{ {-1, -1}, {0, -1}, {0, 0}, {1, 0} }},
                {{ {0, -1}, {1, -1}, {-1, 0}, {0, 0} }},
                {{ {0, -1}, {-1, 0}, {0, 0}, {1, 0} }},
                {{ {-1, -1}, {-1, 0}, {0, 0}, {1, 0} }},
                {{ {1, -1}, {-1, 0}, {0, 0}, {1, 0} }},
            },
            {
                get_color_id(ColorIdName::dark_candy_apple_red),
                get_color_id(ColorIdName::islamic_green),
                get_color_id(ColorIdName::windsor_tan),
                get_color_id(ColorIdName::heliotrope_magenta),
                get_color_id(ColorIdName::tiffany_blue),
                get_color_id(ColorIdName::sunset_orange),
                get_color_id(ColorIdName::screamin_green),
                get_color_id(ColorIdName::dodie_yellow),
                get_color_id(ColorIdName::very_light_blue),
                get_color_id(ColorIdName::shocking_pink),
                get_color_id(ColorIdName::electric_blue),
            },
            {
                1,
                true,
            },
            {4, 1},
            10,
        },
        {
            {
                'p',
                'q',
                -1,
            }
        },
    };
    TimerImpl timer{
        config.game.default_settings.start_level,
    };
    ConsoleMatrixDisplayImpl matrix{
        config.ui.display.size,
        config.ui.display.pixel_size,
        config.ui.display.max_color_value,
        {   
            L' ',
            L'·',
            L'◦',
            L'◌',
            L'○',
            L'◎',
            L'◉',
            L'●',
        },
        {{
            {0, 16},
            {1, 1},
            {2, 2},
            {3, 3},
            {4, 4},
            {5, 5},
            {6, 6},
            {7, 7},
            {8, 8},
            {9, 9},
            {10, 10},
            {11, 11},
            {12, 12},
            {13, 13},
            {14, 14},
            {15, 15},
        }},
    };
    MatrixDisplayGameUiImpl ui{
        matrix,
        config.ui.controls,
        config.ui.components,
        config.ui.colors,
        config.ui.cube_size,
    };
    BoardImpl board{
        config.game.board.size,
        config.game.board.offset,
    };
    RngImpl rng{};
    BrickGeneratorImpl brick_generator{
        {config.game.bricks, rng},
        {config.game.color_ids, rng},
    };
    ScoreCounterImpl score_counter{
        config.game.score_counter.score_for,
    };
    GameImpl game{
        ui,
        board,
        brick_generator,
        score_counter,
        config.game.default_settings,
        config.game.brick_spawn_position,
        config.game.next_level_lines_quantity,
    };
    ConsoleGameControllerImpl game_controller{
        timer,
        game,
        matrix.get_game_window(),
        config.controller.key_codes,
    };
  
    timer.connect_timeout([&game](){ game.handle_timeout(); });
    ui.connect_move_left_pressed([&game](){ game.handle_move_left(); });
    ui.connect_move_right_pressed([&game](){ game.handle_move_right(); });
    ui.connect_rotate_clockwise_pressed(
        [&game](){ game.handle_rotate_clockwise(); });
    ui.connect_rotate_counter_clockwise_pressed(
        [&game](){ game.handle_rotate_counter_clockwise(); });
    ui.connect_soft_drop_pressed([&game](){ game.handle_soft_drop(); });
    ui.connect_locking_hard_drop_pressed(
        [&game](){ game.handle_locking_hard_drop(); });
    ui.connect_no_locking_hard_drop_pressed(
        [&game](){ game.handle_no_locking_hard_drop(); });
    ui.connect_hold_pressed([&game](){ game.handle_hold(); });
    game.connect_reset_timeout([&timer](){ timer.reset_timeout(); });
    game.connect_set_timeout_delay(
        [&timer](int level){ timer.set_timeout_delay(level); });
    game_controller.connect_key_press(
        [&ui](int key_code){ui.handle_key_press(key_code);});
    
    game_controller.run();

    return 0;
}