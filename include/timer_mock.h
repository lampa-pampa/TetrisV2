#ifndef INCLUDE_TIMER_MOCK_H
#define INCLUDE_TIMER_MOCK_H

#include "timer.h"

#include <functional>

#include <boost/signals2.hpp>

namespace Tetris
{

class TimerMock final: public Timer
{
public:
    void start() override {}
    void stop() override {}
    void connect_timeout(const std::function<void()>& handler) override {}

private:
    using Signal = boost::signals2::signal<void()>;
    
    Signal timeout;
};

}

#endif