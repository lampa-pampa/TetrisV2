#include "config/filled_config.h"

#include "config/config.h"
#include "ui/color/color_id_name.h"
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
                Ui::ColorIdName::black, // background color
                {
                    // game state
                    {{17, 1}, {30, 63}},
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
                {{1, 0}, {15, 10}},
                {
                    // container
                    Ui::ColorIdName::black,
                },
                {14, 10},
                true,
            },
            {
                // LEVEL
                {
                    {
                        // label
                        "LEVEL",
                        {
                            {{2, 11}, {13, 41}},
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
                            {{3, 55}, {11, 5}},
                            {
                                // container
                                Ui::ColorIdName::black,
                                {2},
                                Ui::ColorIdName::white,
                            },
                            Ui::fixed_width_font,
                            Ui::ColorIdName::sunset_orange,
                        },
                    },
                },
                {
                    // progress bar
                    {{3, 12}, {11, 39}},
                    {
                        // container
                        Ui::ColorIdName::black,
                        {2, 1},
                        Ui::ColorIdName::white,
                    },
                    Ui::ColorIdName::islamic_green,
                    Ui::ColorIdName::davy_s_grey,
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
                {{48, 0}, {15, 30}},
                {
                    // container
                    Ui::ColorIdName::black,
                },
                {14, 10},
            },
            {
                // SCORE
                {
                    // label
                    "SCO",
                    {
                        {{50, 32}, {11, 7}},
                        {
                            // container
                            Ui::ColorIdName::black,
                            {2, 1},
                            Ui::ColorIdName::white,
                        },
                        Ui::fixed_width_font,
                        Ui::ColorIdName::sunset_orange,
                        Ui::Align::center,
                    },
                },
                {
                    // value
                    9,
                    {
                        {{50, 43}, {11, 17}},
                        {
                            // container
                            Ui::ColorIdName::black,
                            {2},
                            Ui::ColorIdName::white,
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
                Ui::ColorIdName::electric_blue,
                {1, 0},
            },
            {
                {{0, -1}, {1, -1}, {0, 0}, {1, 0}},
                Ui::ColorIdName::dodie_yellow,
                {0, -1},
            },
            {
                {{-1, -1}, {0, -1}, {0, 0}, {1, 0}},
                Ui::ColorIdName::dark_candy_apple_red,
            },
            {
                {{0, -1}, {1, -1}, {-1, 0}, {0, 0}},
                Ui::ColorIdName::screamin_green,
            },
            {
                {{0, -1}, {-1, 0}, {0, 0}, {1, 0}},
                Ui::ColorIdName::heliotrope_magenta,
            },
            {
                {{-1, -1}, {-1, 0}, {0, 0}, {1, 0}},
                Ui::ColorIdName::duke_blue,
            },
            {
                {{1, -1}, {-1, 0}, {0, 0}, {1, 0}},
                Ui::ColorIdName::windsor_tan,
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
