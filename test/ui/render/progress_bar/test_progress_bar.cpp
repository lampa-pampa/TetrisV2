#include "ui/color/color_name.h"
#include "ui/render/progress_bar/progress_bar.h"

#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <tuple>
#include <utility>
#include <vector>

#include "ui/render/sprite.h"

using std::pair;
using std::tuple;
using std::vector;
using testing::Eq;
using Tetris::Ui::ColorName;
using Tetris::Ui::RenderProgressBar;
using Tetris::Ui::Sprites;

TEST(RenderProgressBar, render)
{
    vector<pair<tuple<RenderProgressBar, int>, Sprites>>
        render_progress_bar_and_count_to_expected{
            {
                {
                    {
                        {{0, 0}, {2}},
                        {
                            ColorName::black,
                        },
                        ColorName::sunset_orange,
                        ColorName::black,
                        {2, 1},
                        2,
                        0,
                    },
                    0,
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
                        {0, 0},
                        {
                            {0, 0},
                            {1, 0},
                        },
                        ColorName::black,
                    },
                    {
                        {0, 1},
                        {
                            {0, 0},
                            {1, 0},
                        },
                        ColorName::black,
                    },
                },
            },
            {
                {
                    {
                        {{1, 2}, {2, 5}},
                        {
                            ColorName::white,
                        },
                        ColorName::sunset_orange,
                        ColorName::black,
                        {2, 1},
                        3,
                        1,
                    },
                    2,
                },
                {
                    {
                        {1, 2},
                        {
                            {0, 0},
                            {1, 0},
                            {0, 1},
                            {1, 1},
                            {0, 2},
                            {1, 2},
                            {0, 3},
                            {1, 3},
                            {0, 4},
                            {1, 4},
                        },
                        ColorName::white,
                    },
                    {
                        {1, 2},
                        {
                            {0, 0},
                            {1, 0},
                        },
                        ColorName::black,
                    },
                    {
                        {1, 4},
                        {
                            {0, 0},
                            {1, 0},
                        },
                        ColorName::sunset_orange,
                    },
                    {
                        {1, 6},
                        {
                            {0, 0},
                            {1, 0},
                        },
                        ColorName::sunset_orange,
                    },
                },
            },
            {
                {
                    {
                        {{4, 7}, {2, 5}},
                        {
                            ColorName::white,
                        },
                        ColorName::sunset_orange,
                        ColorName::black,
                        {1, 1},
                        5,
                        0,
                    },
                    3,
                },
                {
                    {
                        {4, 7},
                        {
                            {0, 0},
                            {1, 0},
                            {0, 1},
                            {1, 1},
                            {0, 2},
                            {1, 2},
                            {0, 3},
                            {1, 3},
                            {0, 4},
                            {1, 4},
                        },
                        ColorName::white,
                    },
                    {
                        {4, 7},
                        {
                            {0, 0},
                        },
                        ColorName::black,
                    },
                    {
                        {4, 8},
                        {
                            {0, 0},
                        },
                        ColorName::black,
                    },
                    {
                        {4, 9},
                        {
                            {0, 0},
                        },
                        ColorName::sunset_orange,
                    },
                    {
                        {4, 10},
                        {
                            {0, 0},
                        },
                        ColorName::sunset_orange,
                    },
                    {
                        {4, 11},
                        {
                            {0, 0},
                        },
                        ColorName::sunset_orange,
                    },
                },
            },
        };

    for (const auto& pair : render_progress_bar_and_count_to_expected)
    {
        const auto& [render_progress_bar, count]{pair.first};

        ASSERT_THAT(render_progress_bar.render(count), Eq(pair.second));
    }
}
