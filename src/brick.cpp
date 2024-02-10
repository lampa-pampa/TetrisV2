#include "brick.h"

int Brick::get_min_x()
{
    int min_x = this->pixels[0].coords.x;
    for(auto it = this->pixels.begin() + 1; it != this->pixels.end(); ++it)
    {
        if(it->coords.x < min_x)
            min_x = it->coords.x;
    }
    return min_x;
}