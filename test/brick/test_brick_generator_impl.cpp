#include "brick/brick_generator_impl.h"

#include <utility>
#include <vector>

#include <boost/range/irange.hpp>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "brick/brick.h"
#include "rng/rng_mock.h"
#include "ui/color/color_id_name.h"

using boost::irange;
using std::pair;
using std::vector;
using testing::Eq;
using Tetris::Brick;
using Tetris::BrickGeneratorImpl;
using Tetris::RngMock;
using Tetris::Ui::ColorIdName;

TEST(BrickGeneratorImpl, generate)
{
    RngMock initial_rng{};
    const vector<pair<BrickGeneratorImpl, vector<Brick>>> gen_to_expected{
        {
            {
                {
                    {
                        {{{1, 0}, {0, 1}}},
                        {{{2, 0}, {0, 2}}},
                    },
                    initial_rng,
                },
                {
                    {ColorIdName::white, ColorIdName::duke_blue},
                    initial_rng,
                },
            },
            {
                {{
                    {1, 0, ColorIdName::white},
                    {0, 1, ColorIdName::white},
                }},
                {{
                    {2, 0, ColorIdName::duke_blue},
                    {0, 2, ColorIdName::duke_blue},
                }},
            },
        },
        {
            {
                {
                    {
                        {{{0, 0}}},
                        {{{1, 1}}},
                    },
                    initial_rng,
                },
                {
                    {ColorIdName::white, ColorIdName::duke_blue},
                    initial_rng,
                },
            },
            {
                {{{0, 0, ColorIdName::white}}},
                {{{1, 1, ColorIdName::duke_blue}}},
            },
        },
        {
            {
                {
                    {
                        {{{0, 0}}},
                        {{{1, 1}}},
                        {{{0, 2}}},
                    },
                    initial_rng,
                },
                {
                    {ColorIdName::white},
                    initial_rng,
                },
            },
            {
                {{{0, 0, ColorIdName::white}}},
                {{{1, 1, ColorIdName::white}}},
                {{{0, 2, ColorIdName::white}}},
            },
        },
    };

    for (const auto& pair : gen_to_expected)
    {
        BrickGeneratorImpl brick_generator{pair.first};
        for (const auto& i : irange(2))
        {
            for (const auto& expected : pair.second)
                ASSERT_THAT(brick_generator.generate(), Eq(expected));
        }
    }
}
