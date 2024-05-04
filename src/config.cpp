#include "config/filled_config.h"

#include "game_controller/game_controller_key_codes.h"
#include "ui/color/color_id_name.h"
#include "ui/game_ui/game_ui_colors.h"
#include "ui/game_ui/game_ui_components.h"
#include "ui/game_ui/game_ui_controls.h"

using Tetris::Ui::ColorIdName;
using Tetris::Ui::GameUiColors;
using Tetris::Ui::GameUiComponents;
using Tetris::Ui::GameUiControls;
using Tetris::Ui::get_color_id;

namespace Tetris
{

const Config config{
    UiConfig{
        GameUiControls{
            0x104,
            0x105,
            0x103,
            0x102,
            ' ',
            'x',
            'z',
            'c',
        },
        GameUiComponents{
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
        GameUiColors{
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
                    140,
                },
            },
        },
        3
    },
    GameConfig{
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
    GameControllerConfig{
        GameControllerKeyCodes{
            'p',
            'q',
            -1,
        }
    },
};

}