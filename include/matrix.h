#ifndef INCLUDE_MATRIX
#define INCLUDE_MATRIX

#include <vector>

namespace Tetris
{

class Matrix
{
    using Pixels = std::vector<std::vector<int>>;

public:   
    virtual void refresh_pixels(Pixels pixels) = 0;
    virtual ~Matrix() = default;
};

}

#endif