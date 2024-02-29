#ifndef INCLUDE_TIMER_MOCK_H
#define INCLUDE_TIMER_MOCK_H

#include <functional>

#include <boost/signals2.hpp>

#include "timer.h"

namespace Tetris
{

class TimerMock final: public Timer
{
    using signal = boost::signals2::signal<void()>;
    
    signal timeout;

public:
    void start() override{}
    void stop() override{}
    void connect_timeout(const std::function<void()> handler) override{}
};

}

#endif