#ifndef INCLUDE_TIMER_IMPL_H
#define INCLUDE_TIMER_IMPL_H

#include "timer.h"

#include <boost/signals2.hpp>
#include <chrono>
#include <functional>
#include <ratio>

namespace Tetris
{

class TimerImpl final: public Timer
{  
public:
    TimerImpl(unsigned long long timeout_delay)
    :
        timeout_delay{timeout_delay}
    {
        this->start();
    }

    void start() override
    {
        this->active = true;
        this->start_time = std::chrono::system_clock::now();
    }

    void stop() override
    {
        this->active = false;
    }

    void connect_timeout(const std::function<void()>& handler) override
    {
        this->timeout_signal.connect(handler);
    }

    void update_time() override
    {
        const auto cur_time{std::chrono::system_clock::now()};
        const auto duration{cur_time - this->start_time};
        if(duration >= this->timeout_delay)
        {
            this->timeout_signal();
            this->start_time += timeout_delay;
        }
    };

    bool is_active() const override
    {
        return this->active;
    }

private:
    using Signal = boost::signals2::signal<void()>;
    using TimePoint = std::chrono::time_point<
        std::chrono::system_clock, std::chrono::duration<
            long, std::ratio<1, 1000000000>>>;

    const std::chrono::milliseconds timeout_delay;
    bool active;
    Signal timeout_signal;
    TimePoint start_time;
};

}

#endif