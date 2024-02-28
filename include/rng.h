#ifndef Rng_H
#define Rng_H

class Rng
{
public:
    virtual int random(int range) = 0;
    virtual ~Rng() = default;
};

#endif