#ifndef TIMER_H
#define TIMER_H

#include <functional>

class Timer
{
    public:
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void connect_timeout(std::function<void()> handler) = 0;
        inline virtual ~Timer() = default;
};

#endif