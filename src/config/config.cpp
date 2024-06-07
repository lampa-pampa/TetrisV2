#include "config/filled_config.h"

#include "config/config.h"
#include "ui/color/color_id_name.h"
#include "ui/game_ui/config.h"
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
                Ui::ColorIdName::white, // background color
                {
                    // game state
                    {{17, 2}, {30, 60}},
                    {
                        // container
                        Ui::ColorIdName::black,
                        {2},
                    },
                    Ui::fixed_width_font,
                    Ui::ColorIdName::sunset_orange,
                    Ui::Align::center,
                    0,
                    {1, 2},
                    false,
                },
            },
            {
                // HOLD
                {2, 2},
                {14, 8},
                {
                    // container
                    Ui::ColorIdName::black,
                },
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
                                Ui::ColorIdName::black,
                                {2},
                            },
                            Ui::fixed_width_font,
                            Ui::ColorIdName::sunset_orange,
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
                                Ui::ColorIdName::black,
                                {1},
                            },
                            Ui::fixed_width_font,
                            Ui::ColorIdName::sunset_orange,
                        },
                    },
                },
                {
                    // progress bar
                    {{3, 13}, {11, 39}},
                    {
                        // container
                        Ui::ColorIdName::black,
                        {1},
                    },
                    Ui::ColorIdName::islamic_green,
                    Ui::ColorIdName::davy_s_grey,
                },
            },
            {
                // BOARD
                {
                    {17, 2},
                },
                64,
            },
            {
                // NEXT
                {48, 2},
                {14, 10},
                {
                    // container
                    Ui::ColorIdName::black,
                },
            },
            {
                // SCORE
                {
                    // label
                    "SCO",
                    {
                        {{50, 35}, {11, 5}},
                        {
                            // container
                            Ui::ColorIdName::black,
                            {1},
                        },
                        Ui::fixed_width_font,
                        Ui::ColorIdName::sunset_orange,
                    },
                },
                {
                    // value
                    9,
                    {
                        {{50, 44}, {11, 17}},
                        {
                            // container
                            Ui::ColorIdName::black,
                            {1},
                        },
                        Ui::fixed_width_font,
                        Ui::ColorIdName::sunset_orange,
                    },
                },
            },
        },
        {
            // STATE MESSAGES
            "PAUSED",
            "GAME\nOVER",
        },
    },
    GameConfig{
        {
            // BOARD
            {10, 20}, // size
            2 // offset
        },
        {
            // SCORE FOR
            1000, // line
            2, // hard drop
            1, // soft drop
        },
        {
            // BRICKS
            {{{-1, 0}, {0, 0}, {1, 0}, {2, 0}}, {1, 0}},
            {{{0, -1}, {1, -1}, {0, 0}, {1, 0}}, {0, -1}},
            {{{-1, -1}, {0, -1}, {0, 0}, {1, 0}}},
            {{{0, -1}, {1, -1}, {-1, 0}, {0, 0}}},
            {{{0, -1}, {-1, 0}, {0, 0}, {1, 0}}},
            {{{-1, -1}, {-1, 0}, {0, 0}, {1, 0}}},
            {{{1, -1}, {-1, 0}, {0, 0}, {1, 0}}},
        },
        {
            // BRICK COLORS
            Ui::ColorIdName::dark_candy_apple_red,
            Ui::ColorIdName::islamic_green,
            Ui::ColorIdName::windsor_tan,
            Ui::ColorIdName::heliotrope_magenta,
            Ui::ColorIdName::tiffany_blue,
            Ui::ColorIdName::sunset_orange,
            Ui::ColorIdName::screamin_green,
            Ui::ColorIdName::dodie_yellow,
            Ui::ColorIdName::very_light_blue,
            Ui::ColorIdName::shocking_pink,
            Ui::ColorIdName::electric_blue,
        },
        {
            // DEFAULT SETTINGS
            1, // start level
            true, // generate ghost
        },
        {4, 1}, // brick spawn position
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
