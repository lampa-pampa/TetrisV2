#include "config/filled_config.h"

#include "brick/brick_name.h"
#include "config/config.h"
#include "ui/color/color_name.h"
#include "ui/game_ui/config.h"
#include "ui/render/text/align.h"
#include "ui/render/text/font/fixed_width.h"

namespace Tetris
{

const Config config{
    Ui::GameUiConfig{
        {
            5, // move left
            7, // move right
            2, // rotate clockwise
            6, // soft drop
            10, // locking hard drop
            9, // no-locking hard drop
            1, // rotate counter-clockwise
            11, // hold
        },
        {
            // GRAPHIC ENGINE
            {
                // MAIN
                Ui::ColorName::black, // background color
                Ui::ColorName::white, // border color
                {
                    {{17, 63}, {30, 1}},
                },
                {
                    // game state
                    {{0, 0}, {63, 63}},
                    {
                        // container
                        Ui::ColorName::black,
                        {2},
                        Ui::ColorName::white,
                    },
                    Ui::fixed_width_font,
                    Ui::ColorName::sunset_orange,
                    Ui::Align::center,
                    0,
                    {1, 2},
                    false,
                },
            },
            {
                // HOLD
                {{1, 1}, {15, 10}},
                {
                    // container
                    Ui::ColorName::black,
                    {0},
                    Ui::ColorName::white,
                },
                {16, 10},
                true,
            },
            {
                // LEVEL
                {
                    // label
                    "LVL",
                    {
                        {{3, 46}, {11, 5}},
                        {
                            // container
                            Ui::ColorName::black,
                            {2},
                            Ui::ColorName::white,
                        },
                        Ui::fixed_width_font,
                        Ui::ColorName::sunset_orange,
                    },
                },
                {
                    // value
                    9,
                    {
                        {{3, 56}, {11, 5}},
                        {
                            // container
                            Ui::ColorName::black,
                            {2},
                            Ui::ColorName::white,
                        },
                        Ui::fixed_width_font,
                        Ui::ColorName::sunset_orange,
                    },
                },
            },
            {
                // PROGRESS BAR
                {{3, 13}, {11, 29}},
                {
                    // container
                    {Ui::ColorName::davy_s_grey, 0x44},
                    {2, 1},
                    Ui::ColorName::white,
                },
                Ui::ColorName::sunset_orange,
                Ui::ColorName::black,
            },
            {
                // BOARD
                {
                    {17, 0},
                },
                64,
            },
            {
                // NEXT
                {{48, 1}, {15, 30}},
                {
                    // container
                    Ui::ColorName::black,
                    {0},
                    Ui::ColorName::white,
                },
                {14, 10},
            },
            {
                // SCORE
                {
                    // label
                    "SCO",
                    {
                        {{50, 33}, {11, 7}},
                        {
                            // container
                            Ui::ColorName::black,
                            {2, 1},
                            Ui::ColorName::white,
                        },
                        Ui::fixed_width_font,
                        Ui::ColorName::sunset_orange,
                        Ui::Align::center,
                    },
                },
                {
                    // value
                    9,
                    {
                        {{50, 44}, {11, 17}},
                        {
                            // container
                            Ui::ColorName::black,
                            {2},
                            Ui::ColorName::white,
                        },
                        Ui::fixed_width_font,
                        Ui::ColorName::sunset_orange,
                    },
                },
            },
        },
        {
            // BRICK NAME TO COLOR NAME
            {BrickName::empty, Ui::ColorName::black},
            {BrickName::I, Ui::ColorName::electric_blue},
            {BrickName::O, Ui::ColorName::dodie_yellow},
            {BrickName::Z, Ui::ColorName::dark_candy_apple_red},
            {BrickName::S, Ui::ColorName::screamin_green},
            {BrickName::T, Ui::ColorName::heliotrope_magenta},
            {BrickName::J, Ui::ColorName::duke_blue},
            {BrickName::L, Ui::ColorName::windsor_tan},
        },
        {
            // STATE MESSAGES
            " PAUSED ",
            "GAME OVER",
        },
    },
    GameConfig{
        {
            // BOARD
            {10, 21}, // size
        },
        {
            // SCORE FOR
            1000, // line
            2, // hard drop
            1, // soft drop
        },
        {
            // BRICKS
            {
                {{-1, 0}, {0, 0}, {1, 0}, {2, 0}},
                BrickName::I,
                {1, 0},
            },
            {
                {{0, -1}, {1, -1}, {0, 0}, {1, 0}},
                BrickName::O,
                {0, -1},
            },
            {
                {{-1, -1}, {0, -1}, {0, 0}, {1, 0}},
                BrickName::Z,
            },
            {
                {{0, -1}, {1, -1}, {-1, 0}, {0, 0}},
                BrickName::S,
            },
            {
                {{0, -1}, {-1, 0}, {0, 0}, {1, 0}},
                BrickName::T,
            },
            {
                {{-1, -1}, {-1, 0}, {0, 0}, {1, 0}},
                BrickName::J,
            },
            {
                {{1, -1}, {-1, 0}, {0, 0}, {1, 0}},
                BrickName::L,
            },
        },
        {
            // DEFAULT SETTINGS
            1, // start level
            true, // generate ghost
        },
        {4, 2}, // brick spawn position
    },
    {
        // GAME CONTROLLER
        {
            // KEY CODES
            3, // pause
            4, // quit
            -1, // no key
        },
    },
};

}
