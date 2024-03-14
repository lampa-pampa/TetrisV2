#ifndef INCLUDE_TIMER_H
#define INCLUDE_TIMER_H

#include <functional>

namespace Tetris
{

class Timer
{
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void reset_timeout() = 0;
    virtual void set_timeout_delay(int level) = 0;
    virtual void connect_timeout(const std::function<void()>& handler) = 0;
    virtual void update_time() = 0;
    virtual bool is_active() const = 0;
    virtual ~Timer() = default;
};

}

#endif