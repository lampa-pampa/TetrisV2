#ifndef INCLUDE_UI_CHAR_H
#define INCLUDE_UI_CHAR_H

#include <cassert>
#include <map>
#include <vector>

#include "vector_2.h"

namespace Tetris
{

struct UiChar final
{
    static constexpr int width{3};
    static constexpr int height{5};
    static constexpr int separator{1};
    
    static int get_text_width(int length)
    {
        return length * (width + separator) - separator;
    }

    static int get_max_text_length(int container_width)
    {
        return (container_width + separator) / (width + separator);
    }

    std::vector<Vector2> pixels;
};

namespace
{
    const std::map<char, UiChar> char_to_ui_char
    {
        {'0', {{
            {0, 0}, {1, 0}, {2, 0},
            {0, 1},         {2, 1},
            {0, 2},         {2, 2},
            {0, 3},         {2, 3},
            {0, 4}, {1, 4}, {2, 4},
        }}},
        {'1', {{
            {2, 0},
            {2, 1},
            {2, 2},
            {2, 3},
            {2, 4},
        }}},
        {'2', {{
            {0, 0}, {1, 0}, {2, 0},
                            {2, 1},
            {0, 2}, {1, 2}, {2, 2},
            {0, 3},
            {0, 4}, {1, 4}, {2, 4},
        }}},
        {'3', {{
            {0, 0}, {1, 0}, {2, 0},
                            {2, 1},
            {0, 2}, {1, 2}, {2, 2},
                            {2, 3},
            {0, 4}, {1, 4}, {2, 4},
        }}},
        {'4', {{
            {0, 0},         {2, 0},
            {0, 1},         {2, 1},
            {0, 2}, {1, 2}, {2, 2},
                            {2, 3},
                            {2, 4},
        }}},
        {'5', {{
            {0, 0}, {1, 0}, {2, 0},
            {0, 1},
            {0, 2}, {1, 2}, {2, 2},
                            {2, 3},
            {0, 4}, {1, 4}, {2, 4},
        }}},
        {'6', {{
            {0, 0}, {1, 0}, {2, 0},
            {0, 1},
            {0, 2}, {1, 2}, {2, 2},
            {0, 3},         {2, 3},
            {0, 4}, {1, 4}, {2, 4},
        }}},
        {'7', {{
            {0, 0}, {1, 0}, {2, 0},
                            {2, 1},
                            {2, 2},
                            {2, 3},
                            {2, 4},
        }}},
        {'8', {{
            {0, 0}, {1, 0}, {2, 0},
            {0, 1},         {2, 1},
            {0, 2}, {1, 2}, {2, 2},
            {0, 3},         {2, 3},
            {0, 4}, {1, 4}, {2, 4},
        }}},
        {'9', {{
            {0, 0}, {1, 0}, {2, 0},
            {0, 1},         {2, 1},
            {0, 2}, {1, 2}, {2, 2},
                            {2, 3},
            {0, 4}, {1, 4}, {2, 4},
        }}},
        {'P', {{
            {0, 0}, {1, 0}, {2, 0},
            {0, 1},         {2, 1},
            {0, 2}, {1, 2}, {2, 2},
            {0, 3},
            {0, 4},
        }}},
        {'A', {{
            {0, 0}, {1, 0}, {2, 0},
            {0, 1},         {2, 1},
            {0, 2}, {1, 2}, {2, 2},
            {0, 3},         {2, 3},
            {0, 4},         {2, 4},
        }}},
        {'U', {{
            {0, 0},         {2, 0},
            {0, 1},         {2, 1},
            {0, 2},         {2, 2},
            {0, 3},         {2, 3},
            {0, 4}, {1, 4}, {2, 4},
        }}},
        {'S', {{
            {0, 0}, {1, 0}, {2, 0},
            {0, 1},
            {0, 2}, {1, 2}, {2, 2},
                            {2, 3},
            {0, 4}, {1, 4}, {2, 4},
        }}},
        {'E', {{
            {0, 0}, {1, 0}, {2, 0},
            {0, 1},
            {0, 2}, {1, 2}, {2, 2},
            {0, 3},
            {0, 4}, {1, 4}, {2, 4},
        }}},
        {'D', {{
            {0, 0}, {1, 0},
            {0, 1},         {2, 1},
            {0, 2},         {2, 2},
            {0, 3},         {2, 3},
            {0, 4}, {1, 4},
        }}},
        {'L', {{
            {0, 0},
            {0, 1},
            {0, 2},
            {0, 3},
            {0, 4}, {1, 4}, {2, 4},
        }}},
        {'V', {{
            {0, 0},         {2, 0},
            {0, 1},         {2, 1},
            {0, 2},         {2, 2},
                    {1, 3},
                    {1, 4},
        }}},
    };
}

inline UiChar get_ui_char(char c)
{
    const auto it{char_to_ui_char.find(c)};
    assert(it != char_to_ui_char.end());
    return it->second;
}

}

#endif