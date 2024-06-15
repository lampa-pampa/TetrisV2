#include "ui/render/container/container.h"

#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "ui/color/color_name.h"
#include "ui/render/rectangle.h"
#include "ui/render/sprite.h"

using std::pair;
using std::tuple;
using std::vector;
using testing::Eq;
using Tetris::Ui::ColorName;
using Tetris::Ui::Rectangle;
using Tetris::Ui::RenderContainer;
using Tetris::Ui::Sprites;

TEST(RenderContainer, render)
{
    vector<pair<tuple<RenderContainer, Rectangle>, Sprites>>
        render_container_and_rectangle_to_expected{
            {
                {
                    {
                        ColorName::black,
                    },
                    {{0, 0}, {2, 3}},
                },
                {
                    {
                        {0, 0},
                        {
                            {0, 0},
                            {1, 0},
                            {0, 1},
                            {1, 1},
                            {0, 2},
                            {1, 2},
                        },
                        ColorName::black,
                    },
                },
            },
            {
                {
                    {
                        ColorName::white,
                        {2, 1},
                    },
                    {{5, 8}, {2}},
                },
                {
                    {
                        {3, 7},
                        {
                            {0, 0},
                            {1, 0},
                            {2, 0},
                            {3, 0},
                            {4, 0},
                            {5, 0},
                            {0, 1},
                            {1, 1},
                            {2, 1},
                            {3, 1},
                            {4, 1},
                            {5, 1},
                            {0, 2},
                            {1, 2},
                            {2, 2},
                            {3, 2},
                            {4, 2},
                            {5, 2},
                            {0, 3},
                            {1, 3},
                            {2, 3},
                            {3, 3},
                            {4, 3},
                            {5, 3},
                        },
                        ColorName::white,
                    },
                },
            },
            {
                {
                    {
                        ColorName::black,
                        {1, 2},
                        ColorName::white,
                        1,
                    },
                    {{12, 3}, {1}},
                },
                {
                    {
                        {11, 1},
                        {
                            {0, 0},
                            {1, 0},
                            {2, 0},
                            {0, 1},
                            {1, 1},
                            {2, 1},
                            {0, 2},
                            {1, 2},
                            {2, 2},
                            {0, 3},
                            {1, 3},
                            {2, 3},
                            {0, 4},
                            {1, 4},
                            {2, 4},
                        },
                        ColorName::black,
                    },
                    {
                        {10, 0},
                        {
                            {0, 0},
                            {1, 0},
                            {2, 0},
                            {3, 0},
                            {4, 0},
                        },
                        ColorName::white,
                    },
                    {
                        {10, 1},
                        {
                            {0, 0},
                            {0, 1},
                            {0, 2},
                            {0, 3},
                            {0, 4},
                        },
                        ColorName::white,
                    },
                    {
                        {14, 1},
                        {
                            {0, 0},
                            {0, 1},
                            {0, 2},
                            {0, 3},
                            {0, 4},
                        },
                        ColorName::white,
                    },
                    {
                        {10, 6},
                        {
                            {0, 0},
                            {1, 0},
                            {2, 0},
                            {3, 0},
                            {4, 0},
                        },
                        ColorName::white,
                    },
                },
            },
        };

    for (const auto& pair : render_container_and_rectangle_to_expected)
    {
        const auto& [render_container, rectangle]{pair.first};
        ASSERT_THAT(render_container.render(rectangle), Eq(pair.second));
    }
}
