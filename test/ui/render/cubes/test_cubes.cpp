#include <cstdint>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdint>
#include <map>
#include <utility>
#include <vector>

#include "brick/brick_name.h"
#include "cube/cube.h"
#include "ui/color/color_name.h"
#include "ui/render/cubes/cubes.h"
#include "ui/render/sprite.h"

using std::map;
using std::pair;
using std::tuple;
using std::vector;
using testing::Eq;
using Tetris::BrickName;
using Tetris::Cube;
using Tetris::Ui::ColorName;
using Tetris::Ui::RenderCubes;
using Tetris::Ui::Sprites;

TEST(RenderCubes, render)
{
    const map<BrickName, ColorName> initial_brick_name_to_color_name{
        {BrickName::empty, ColorName::black},
        {BrickName::I, ColorName::electric_blue},
        {BrickName::O, ColorName::dodie_yellow},
        {BrickName::Z, ColorName::dark_candy_apple_red},
    };
    const vector<
        pair<tuple<RenderCubes, vector<Cube>, uint_fast8_t, bool>, Sprites>>
        test_cases{
            {
                {
                    {
                        {0, 0},
                        2,
                    },
                    {
                        {0, 0, BrickName::empty},
                        {1, 0, BrickName::I},
                        {0, 1, BrickName::O},
                        {1, 1, BrickName::Z},
                    },
                    0xff,
                    true,
                },
                {
                    {
                        {0, 0},
                        {
                            {0, 0},
                            {1, 0},
                            {0, 1},
                            {1, 1},
                        },
                        ColorName::black,
                    },
                    {
                        {2, 0},
                        {
                            {0, 0},
                            {1, 0},
                            {0, 1},
                            {1, 1},
                        },
                        ColorName::electric_blue,
                    },
                    {
                        {0, 2},
                        {
                            {0, 0},
                            {1, 0},
                            {0, 1},
                            {1, 1},
                        },
                        ColorName::dodie_yellow,
                    },
                    {
                        {2, 2},
                        {
                            {0, 0},
                            {1, 0},
                            {0, 1},
                            {1, 1},
                        },
                        ColorName::dark_candy_apple_red,
                    },
                },
            },
            {
                {
                    {
                        {7, 5},
                        2,
                    },
                    {
                        {0, 0, BrickName::empty},
                        {1, 0, BrickName::I},
                        {0, 1, BrickName::O},
                        {1, 1, BrickName::Z},
                    },
                    0x88,
                    true,
                },
                {
                    {
                        {7, 5},
                        {
                            {0, 0},
                            {1, 0},
                            {0, 1},
                            {1, 1},
                        },
                        ColorName::black,
                    },
                    {
                        {9, 5},
                        {
                            {0, 0},
                            {1, 0},
                            {0, 1},
                            {1, 1},
                        },
                        {ColorName::electric_blue, 0x88},
                    },
                    {
                        {7, 7},
                        {
                            {0, 0},
                            {1, 0},
                            {0, 1},
                            {1, 1},
                        },
                        {ColorName::dodie_yellow, 0x88},
                    },
                    {
                        {9, 7},
                        {
                            {0, 0},
                            {1, 0},
                            {0, 1},
                            {1, 1},
                        },
                        {ColorName::dark_candy_apple_red, 0x88},
                    },
                },
            },
            {
                {
                    {
                        {9, 8},
                        3,
                    },
                    {
                        {-1, 0, BrickName::I},
                        {0, 0, BrickName::I},
                        {1, 0, BrickName::I},
                        {0, 1, BrickName::O},
                        {1, 1, BrickName::Z},
                    },
                    0xff,
                    false,
                },
                {
                    {
                        {6, 8},
                        {
                            {0, 0},
                        },
                        ColorName::electric_blue,
                    },
                    {
                        {7, 8},
                        {
                            {0, 0},
                        },
                        ColorName::electric_blue,
                    },
                    {
                        {8, 8},
                        {
                            {0, 0},
                        },
                        ColorName::electric_blue,
                    },
                    {
                        {6, 9},
                        {
                            {0, 0},
                        },
                        ColorName::electric_blue,
                    },
                    {
                        {6, 10},
                        {
                            {0, 0},
                        },
                        ColorName::electric_blue,
                    },
                    {
                        {7, 10},
                        {
                            {0, 0},
                        },
                        ColorName::electric_blue,
                    },
                    {
                        {8, 10},
                        {
                            {0, 0},
                        },
                        ColorName::electric_blue,
                    },
                    {
                        {9, 8},
                        {
                            {0, 0},
                        },
                        ColorName::electric_blue,
                    },
                    {
                        {10, 8},
                        {
                            {0, 0},
                        },
                        ColorName::electric_blue,
                    },
                    {
                        {11, 8},
                        {
                            {0, 0},
                        },
                        ColorName::electric_blue,
                    },
                    {
                        {9, 10},
                        {
                            {0, 0},
                        },
                        ColorName::electric_blue,
                    },
                    {
                        {10, 10},
                        {
                            {0, 0},
                        },
                        ColorName::electric_blue,
                    },
                    {
                        {11, 10},
                        {
                            {0, 0},
                        },
                        ColorName::electric_blue,
                    },
                    {
                        {12, 8},
                        {
                            {0, 0},
                        },
                        ColorName::electric_blue,
                    },
                    {
                        {13, 8},
                        {
                            {0, 0},
                        },
                        ColorName::electric_blue,
                    },
                    {
                        {14, 8},
                        {
                            {0, 0},
                        },
                        ColorName::electric_blue,
                    },
                    {
                        {14, 9},
                        {
                            {0, 0},
                        },
                        ColorName::electric_blue,
                    },
                    {
                        {12, 10},
                        {
                            {0, 0},
                        },
                        ColorName::electric_blue,
                    },
                    {
                        {13, 10},
                        {
                            {0, 0},
                        },
                        ColorName::electric_blue,
                    },
                    {
                        {14, 10},
                        {
                            {0, 0},
                        },
                        ColorName::electric_blue,
                    },
                    {
                        {9, 11},
                        {
                            {0, 0},
                        },
                        ColorName::dodie_yellow,
                    },
                    {
                        {10, 11},
                        {
                            {0, 0},
                        },
                        ColorName::dodie_yellow,
                    },
                    {
                        {11, 11},
                        {
                            {0, 0},
                        },
                        ColorName::dodie_yellow,
                    },
                    {
                        {9, 12},
                        {
                            {0, 0},
                        },
                        ColorName::dodie_yellow,
                    },
                    {
                        {11, 12},
                        {
                            {0, 0},
                        },
                        ColorName::dodie_yellow,
                    },
                    {
                        {9, 13},
                        {
                            {0, 0},
                        },
                        ColorName::dodie_yellow,
                    },
                    {
                        {10, 13},
                        {
                            {0, 0},
                        },
                        ColorName::dodie_yellow,
                    },
                    {
                        {11, 13},
                        {
                            {0, 0},
                        },
                        ColorName::dodie_yellow,
                    },
                    {
                        {12, 11},
                        {
                            {0, 0},
                        },
                        ColorName::dark_candy_apple_red,
                    },
                    {
                        {13, 11},
                        {
                            {0, 0},
                        },
                        ColorName::dark_candy_apple_red,
                    },
                    {
                        {14, 11},
                        {
                            {0, 0},
                        },
                        ColorName::dark_candy_apple_red,
                    },
                    {
                        {12, 12},
                        {
                            {0, 0},
                        },
                        ColorName::dark_candy_apple_red,
                    },
                    {
                        {14, 12},
                        {
                            {0, 0},
                        },
                        ColorName::dark_candy_apple_red,
                    },
                    {
                        {12, 13},
                        {
                            {0, 0},
                        },
                        ColorName::dark_candy_apple_red,
                    },
                    {
                        {13, 13},
                        {
                            {0, 0},
                        },
                        ColorName::dark_candy_apple_red,
                    },
                    {
                        {14, 13},
                        {
                            {0, 0},
                        },
                        ColorName::dark_candy_apple_red,
                    },
                },
            },
        };

    for (const auto& pair : test_cases)
    {
        const auto& [render_cubes, cubes, color_value, fill]{pair.first};
        const Sprites actual{render_cubes.render(
            cubes, initial_brick_name_to_color_name, color_value, fill)};
        ASSERT_THAT(actual, Eq(pair.second));
    }
}
