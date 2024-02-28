#ifndef INCLUDE_Rng_H
#define INCLUDE_Rng_H

class Rng
{
public:
    virtual int random(int range) = 0;
    virtual ~Rng() = default;
};

#endif