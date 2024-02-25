#include "timer_mock.h"
#include <functional>

using std::function;

void TimerMock::start(){}

void TimerMock::stop(){}

void TimerMock::connect_timeout(const function<void()> handler){}