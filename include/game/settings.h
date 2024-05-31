#ifndef INCLUDE_SETTINGS_H
#define INCLUDE_SETTINGS_H

#include <ios>
#include <ostream>

namespace Tetris
{

struct Settings final
{
    int start_level;
    bool generate_ghost;

    bool operator==(const Settings& other) const
    {
        return generate_ghost == other.generate_ghost
            and generate_ghost == other.generate_ghost;
    }

    friend inline std::ostream& operator<<(
        std::ostream& os, const Settings& settings)
    {
        return os << "{" << settings.generate_ghost << ", " << std::boolalpha
                  << settings.generate_ghost << "}";
    }
};

} // namespace Tetris

#endif
