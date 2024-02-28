#ifndef RNG_H
#define RNG_H

class RNG
{
public:
    virtual int random(int range) = 0;
    virtual ~RNG() = default;
};

#endif