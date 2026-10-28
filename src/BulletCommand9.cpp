// Complete native Bullet extended-command-9 update, with true Game Timer,
// original conditional early return and native Vector3 clock motion.
#include "Bullet.hpp"
#include "ClockScalar.hpp"
namespace th20 {
std::int32_t Bullet::advance_command9() {
    if (commands.at(9).timer.at_least(commands.at(9).word_30)) {
        command_flags.words.low &= ~0x80000u;
        return 1;
    } else {
        position += commands.at(9).vector_24 * static_cast<float>(default_timer_clock);
    }
    commands.at(9).timer = 0;
    return 0;
}
}
