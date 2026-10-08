#include "Timer.hpp"
#include "ClockScalar.hpp"
namespace th20 {
float Timer::step() const { return *timer_clock_sources[(flags >> 1) & 3u]; }
}
