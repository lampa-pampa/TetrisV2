#ifndef INCLUDE_TIMER_IMPL_H
#define INCLUDE_TIMER_IMPL_H

#include "timer.h"

#include <boost/signals2.hpp>
#include <chrono>
#include <cmath>
#include <functional>

namespace Tetris
{

class TimerImpl final: public Timer
{  
public:
    TimerImpl()
    :
        timeout_time{Nanoseconds::zero()}
    {
        this->set_timeout_delay(1);
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
        this->timeout_time = Nanoseconds::zero();
    }

    void set_timeout_delay(int level) override
    {
        this->timeout_delay = this->compute_timeout_delay(level);
    }

    void connect_timeout(const std::function<void()>& handler) override
    {
        this->timeout_signal.connect(handler);
    }

    void update_time() override
    {
        const auto cur_time{std::chrono::system_clock::now()};
        const auto duration{cur_time - this->start_time};
        this->time_elapsed(duration);
    };

    bool is_active() const override
    {
        return this->active;
    }

private:
    using Signal = boost::signals2::signal<void()>;
    using Nanoseconds = std::chrono::nanoseconds;
    using TimePoint = std::chrono::time_point<
        std::chrono::system_clock, Nanoseconds>;

    Nanoseconds timeout_delay;
    Nanoseconds timeout_time;
    bool active;
    Signal timeout_signal;
    TimePoint start_time;

    void time_elapsed(Nanoseconds time)
    {
        this->timeout_time += time;
        if(timeout_time >= this->timeout_delay)
        {
            timeout_time -= timeout_delay;
            this->timeout_signal();
        }
        this->update_start_time();
    }

    void update_start_time()
    {
        this->start_time = std::chrono::system_clock::now();
    }

    Nanoseconds compute_timeout_delay(int level)
    {
        return Nanoseconds{
            static_cast<unsigned long long>(
                std::pow((0.8 - (level - 1) * 0.007), level - 1)
                    * 1'000'000'000
            )
        };
    }
};

}

#endif