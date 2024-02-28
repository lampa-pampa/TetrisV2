#ifndef INCLUDE_TIMER_H
#define INCLUDE_TIMER_H

#include <functional>

class Timer
{
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void connect_timeout(const std::function<void()> handler) = 0;
    virtual ~Timer() = default;
};

#endif