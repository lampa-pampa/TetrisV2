#ifndef INCLUDE_GAME_STATS_H
#define INCLUDE_GAME_STATS_H

namespace Tetris
{

struct GameStats final
{
    unsigned long long score;
    unsigned long long tetrises;
    int lines_count;
    int level;

    constexpr GameStats(int start_level)
      : score{},
        tetrises{},
        lines_count{},
        level{start_level}
    {}
};

} // namespace Tetris

#endif
