#include "config/filled_config.h"

#include "config/config.h"
#include "ui/color/color_id_name.h"

using Tetris::Ui::ColorIdName;
using Tetris::Ui::get_color_id;

namespace Tetris
{

const Config config{
    UiConfig{
        {
            // CONTROLS
            // CONSOLE
            // 0x104,  // move left
            // 0x105,  // move right
            // 0x103,  // rotate clockwise
            // 0x102,  // soft drop
            // ' ',    // locking hard drop
            // 'x',    // no-locking hard drop
            // 'z',    // rotate counter-clockwise
            // 'c',    // hold
            // LED
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
            // UI COMPONENTS
            {
                // CONTAINERS
                {{2, 2}, {14, 8}}, // hold brick
                {{48, 2}, {14, 8}}, // next brick
                {{2, 12}, {13, 41}}, // 'level' text
                {{2, 55}, {13, 7}}, // level value
                {{17, 2}, {30, 60}}, // game board
                {{49, 12}, {13, 7}}, // 'score' text
                {{49, 20}, {13, 19}}, // score value
                {{49, 41}, {13, 7}}, // 'tetrises' text
                {{49, 49}, {13, 13}}, // tetrises value
            },
            {
                // TEXT AREAS
                {{{2, 12}, {13, 41}}, 2}, // 'level' text
                {{{2, 55}, {13, 7}}, 0, 3}, // level value
                {{{17, 2}, {30, 60}}, 2}, // game state
                {{{49, 12}, {13, 7}}}, // 'score' text
                {{{49, 20}, {13, 19}}, 1, 9}, // score value
                {{{49, 41}, {13, 7}}}, // 'tetrises' text
                {{{49, 49}, {13, 13}}, 1, 6}, // tetrises value
            },
            {
                // MESSAGES
                "PAUSED", // paused
                "GAME\nOVER", // game over
                "L\nE\nV\nE\nL", // level
                "SCO", // score
                "TET", // tetrises
            },
            {
                // PROGRESS BARS
                {{3, 13}, {11, 3}, 10, 1}, // level
            },
        },
        {
            // COLORS
            {
                // ID-VALUE
                {get_color_id(ColorIdName::black), 0x00}, // background
                {get_color_id(ColorIdName::white), 0xff}, // border
                {get_color_id(ColorIdName::sunset_orange), 0xff}, // game state
                {
                    // LEVEL
                    {get_color_id(ColorIdName::sunset_orange), 0xff}, // text
                    {get_color_id(ColorIdName::sunset_orange), 0xff}, // value
                    {
                        // PROGRESS BAR
                        {get_color_id(ColorIdName::islamic_green), 0xff}, // on
                        {get_color_id(ColorIdName::davy_s_grey), 0xff}, // off
                    },
                },
                {
                    // SCORE
                    {get_color_id(ColorIdName::sunset_orange), 0xff}, // text
                    {get_color_id(ColorIdName::sunset_orange), 0xff}, // value
                },
                {
                    // TETRISES
                    {get_color_id(ColorIdName::sunset_orange), 0xff}, // text
                    {get_color_id(ColorIdName::sunset_orange), 0xff}, // value
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
            100000, // line
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
            // BRICK COLOR ID'S
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
        // 'p',    // pause
        // 'q',    // quit
        // -1,     // no key
        // LED
        0, // pause
        3, // quit
        -1, // no key
    }},
};

}
