#ifndef INCLUDE_GAME_BRICKS_H
#define INCLUDE_GAME_BRICKS_H

#include <deque>

#include <boost/range/irange.hpp>

#include "brick/bag.h"
#include "brick/brick.h"
#include "vector_2/vector_2.h"

namespace Tetris
{

struct CurBrick final
{
    Brick brick;
    Vector2 position;
    int rotation;
};

struct GameBricks final
{
    static constexpr int next_bricks_count{3};

    Bag<Brick> bag;
    Vector2 start_position;
    Brick hold;
    CurBrick cur;
    std::deque<Brick> next;

    GameBricks(const Bag<Brick>& bag, const Vector2& start_position)
      : bag{bag},
        start_position{start_position},
        hold{},
        cur{}
    {
        next = create_next_bricks();
    }

    std::deque<Brick> create_next_bricks()
    {
        std::deque<Brick> next_bricks{};
        for (const auto& i : boost::irange(next_bricks_count))
            next_bricks.emplace_back(bag.get_next());
        return next_bricks;
    }
};

} // namespace Tetris

#endif
