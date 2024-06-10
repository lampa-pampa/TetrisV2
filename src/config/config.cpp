#include "config/filled_config.h"

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
            13, // move left
            15, // move right
            10, // rotate clockwise
            14, // soft drop
            12, // locking hard drop
            8, // no-locking hard drop
            11, // rotate counter-clockwise
            9, // hold
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
                    {
                        // label
                        "LEVEL",
                        {
                            {{2, 12}, {13, 41}},
                            {
                                // container
                                Ui::ColorName::black,
                                {2},
                            },
                            Ui::fixed_width_font,
                            Ui::ColorName::sunset_orange,
                            Ui::Align::center,
                            1,
                            {1, 2},
                            false,
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
                    // progress bar
                    {{2, 13}, {13, 39}},
                    {
                        // container
                        Ui::ColorName::black,
                        {1},
                        Ui::ColorName::white,
                    },
                    Ui::ColorName::islamic_green,
                    {Ui::ColorName::davy_s_grey, 0x44},
                },
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
                Ui::ColorName::electric_blue,
                {1, 0},
            },
            {
                {{0, -1}, {1, -1}, {0, 0}, {1, 0}},
                Ui::ColorName::dodie_yellow,
                {0, -1},
            },
            {
                {{-1, -1}, {0, -1}, {0, 0}, {1, 0}},
                Ui::ColorName::dark_candy_apple_red,
            },
            {
                {{0, -1}, {1, -1}, {-1, 0}, {0, 0}},
                Ui::ColorName::screamin_green,
            },
            {
                {{0, -1}, {-1, 0}, {0, 0}, {1, 0}},
                Ui::ColorName::heliotrope_magenta,
            },
            {
                {{-1, -1}, {-1, 0}, {0, 0}, {1, 0}},
                Ui::ColorName::duke_blue,
            },
            {
                {{1, -1}, {-1, 0}, {0, 0}, {1, 0}},
                Ui::ColorName::windsor_tan,
            },
        },
        {
            // DEFAULT SETTINGS
            1, // start level
            true, // generate ghost
        },
        {4, 2}, // brick spawn position
        10, // next level lines count
    },
    {
        // GAME CONTROLLER
        {
            // KEY CODES
            0, // pause
            3, // quit
            -1, // no key
        },
    },
};

}
