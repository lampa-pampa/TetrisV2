#ifndef INCLUDE_TIMER_IMPL_H
#define INCLUDE_TIMER_IMPL_H

#include "timer.h"

#include <boost/signals2.hpp>
#include <chrono>
#include <functional>

namespace Tetris
{

class TimerImpl final: public Timer
{  
public:
    TimerImpl(unsigned long long timeout_delay)
    :
        timeout_delay{timeout_delay},
        timeout_time{0}
    {
        this->start();
    }

    void start() override
    {
        this->active = true;
        this->update_start_time();
    }

    void stop() override
    {
        this->active = false;
    }

    void reset_timeout() override
    {
        this->timeout_time = std::chrono::nanoseconds::zero();
    }

    void connect_timeout(const std::function<void()>& handler) override
    {
        this->timeout_signal.connect(handler);
    }

    void update_time() override
    {
        const auto cur_time{std::chrono::system_clock::now()};
        const auto duration{cur_time - this->start_time};
        this->timeout_time += duration;
        if(timeout_time >= this->timeout_delay)
        {
            this->timeout_signal();
            timeout_time -= timeout_delay;
        }
        this->update_start_time();
    };

    bool is_active() const override
    {
        return this->active;
    }

private:
    using Signal = boost::signals2::signal<void()>;
    using TimePoint = std::chrono::time_point<
        std::chrono::system_clock, std::chrono::nanoseconds>;

    const std::chrono::nanoseconds timeout_delay;
    std::chrono::nanoseconds timeout_time;
    bool active;
    Signal timeout_signal;
    TimePoint start_time;

    void update_start_time()
    {
        this->start_time = std::chrono::system_clock::now();
    }
};

}

#endif