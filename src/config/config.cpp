#include "config/filled_config.h"

#include "config/config.h"
#include "ui/color/color_id_name.h"
#include "ui/text_area/align.h"
#include "ui/text_area/font/fixed_width.h"

using Tetris::Ui::ColorIdName;

namespace Tetris
{

const Config config{
    UiConfig{
        {
            // CONTROLS
            // CONSOLE
            0x104, // move left
            0x105, // move right
            0x103, // rotate clockwise
            0x102, // soft drop
            ' ', // locking hard drop
            'x', // no-locking hard drop
            'z', // rotate counter-clockwise
            'c', // hold
                 // LED
                 // 13, // move left
                 // 15, // move right
                 // 10, // rotate clockwise
                 // 14, // soft drop
                 // 12, // locking hard drop
                 // 8, // no-locking hard drop
                 // 11, // rotate counter-clockwise
                 // 9, // hold
        },
        {
            // UI COMPONENTS
            {
                // CONTAINERS
                {{2, 2}, {14, 8}}, // hold brick
                {{48, 2}, {14, 8}}, // next brick
                {{2, 12}, {13, 41}}, // 'LEVEL' text
                {{2, 55}, {13, 7}}, // level value
                {{17, 2}, {30, 60}}, // game board
                {{49, 12}, {13, 7}}, // 'SCO' text
                {{49, 20}, {13, 19}}, // score value
                {{49, 41}, {13, 7}}, // 'TET' text
                {{49, 49}, {13, 13}}, // tetrises value
            },
            {
                // DISPLAYS
                {
                    // game state
                    {{17, 2}, {30, 60}},
                    Ui::fixed_width_font,
                    Ui::Align::center,
                    0,
                    {1, 2},
                    {2},
                },
                {
                    // level
                    {{3, 13}, {11, 3}, 10, 1}, // bar
                    {
                        {
                            // label display
                            {{2, 12}, {13, 41}},
                            Ui::fixed_width_font,
                            Ui::Align::center,
                            0,
                            {2},
                            {2},
                        },
                        "L\nE\nV\nE\nL", // label text
                        {
                            // value display
                            {{2, 55}, {13, 7}},
                            Ui::fixed_width_font,
                        },
                        3, // max value length
                    },
                },
                {
                    // score
                    {
                        // label display
                        {{49, 12}, {13, 7}},
                        Ui::fixed_width_font,
                    },
                    "SCO", // label text
                    {
                        // value display
                        {{49, 20}, {13, 19}},
                        Ui::fixed_width_font,
                    },
                },
                {
                    // tetrises
                    {
                        // label display
                        {{49, 41}, {13, 7}},
                        Ui::fixed_width_font,
                    },
                    "TET", // label text
                    {
                        // value display
                        {{49, 49}, {13, 13}},
                        Ui::fixed_width_font,
                    },
                },
            },
        },
        {
            "PAUSED",
            "GAME\nOVER",
        },
        {
            // COLORS
            {
                // ID-VALUE
                {}, // background
                {ColorIdName::white}, // border
                {
                    // GAME STATE TEXT
                    {ColorIdName::sunset_orange}, // foreground
                    {}, // background
                },
                {
                    // PROGRESS BAR
                    {ColorIdName::islamic_green}, // on
                    {ColorIdName::davy_s_grey}, // off
                },
                {
                    // LEVEL
                    {
                        // TEXT
                        {ColorIdName::sunset_orange}, // foreground
                        {}, // background
                    },
                    {
                        // VALUE
                        {ColorIdName::sunset_orange}, // foreground
                        {}, // background
                    },
                },
                {
                    // SCORE
                    {
                        // TEXT
                        {ColorIdName::sunset_orange}, // foreground
                        {}, // background
                    },
                    {
                        // VALUE
                        {ColorIdName::sunset_orange},
                        {}, // background
                    },
                },
                {
                    // TETRISES
                    {
                        // TEXT
                        {ColorIdName::sunset_orange}, // foreground
                        {}, // background
                    },
                    {
                        // VALUE
                        {ColorIdName::sunset_orange}, // foreground
                        {}, // background
                    },
                },
            },
            {
                // VALUES
                0xff, // board
                {
                    // BRICKS
                    0xff, // hold
                    0xff, // next
                    0xff, // current
                    0x44, // ghost
                },
            },
        },
        3 // CUBE SIZE
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
            ColorIdName::dark_candy_apple_red,
            ColorIdName::islamic_green,
            ColorIdName::windsor_tan,
            ColorIdName::heliotrope_magenta,
            ColorIdName::tiffany_blue,
            ColorIdName::sunset_orange,
            ColorIdName::screamin_green,
            ColorIdName::dodie_yellow,
            ColorIdName::very_light_blue,
            ColorIdName::shocking_pink,
            ColorIdName::electric_blue,
        },
        {
            // DEFAULT SETTINGS
            1, // start level
            true, // generate ghost
        },
        {4, 1}, // brick spawn position
        10, // next level lines quantity
    },
    {{
        // GAME CONTROLLER KEY CODES
        // CONSOLE
        'p', // pause
        'q', // quit
        -1, // no key
        // LED
        // 0, // pause
        // 3, // quit
        // -1, // no key
    }},
};

}
