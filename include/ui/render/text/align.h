#ifndef INCLUDE_UI_ALIGN_H
#define INCLUDE_UI_ALIGN_H

#include <map>
#include <ostream>
#include <string>

namespace Tetris::Ui
{

enum class Align
{
    start,
    center,
    end,
};

const std::map<Align, std::string> align_to_text{
    {Align::start, "start"},
    {Align::center, "center"},
    {Align::end, "end"},
};

inline std::ostream& operator<<(std::ostream& os, Align align)
{
    return os << "Align::" << align_to_text.at(align);
}

} // namespace Tetris::Ui

#endif
