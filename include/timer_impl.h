#ifndef INCLUDE_TIMER_IMPL_H
#define INCLUDE_TIMER_IMPL_H

#include "timer.h"

#include <chrono>
#include <iostream>
#include <functional>
#include <boost/signals2.hpp>

namespace Tetris
{

class TimerImpl final: public Timer
{  
public:
    TimerImpl()
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
        this->timeout.connect(handler);
    }

    void update_time() override
    {
        const auto cur_time{std::chrono::system_clock::now()};
        const auto duration{cur_time - this->start_time};
        std::cerr << duration.count();
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

    Signal timeout;
    bool active;
    TimePoint start_time;
};

}

#endif