#include "EnemyStateScreenOpcode.hpp"
#include "EnemyState.hpp"

namespace th20 {

struct NativeScreenInf;
#if defined(_MSC_VER)
NativeScreenInf* __cdecl screen_factory_4250f0(std::int32_t mode,
    std::uint32_t p1, std::uint32_t p2, std::uint32_t p3, std::uint32_t p4,
    std::int32_t priority, std::uint32_t view);
#else
NativeScreenInf* screen_factory_4250f0(std::int32_t mode,
    std::uint32_t p1, std::uint32_t p2, std::uint32_t p3, std::uint32_t p4,
    std::int32_t priority, std::uint32_t view);
#endif

int execute_enemy_screen_effect_spawn_opcode(EnemyState& state) {
    // The original case reads operand 2, then 1, then 0 before passing them
    // to the ScreenInf factory in the opposite order.
    const std::uint32_t third = static_cast<std::uint32_t>(state.integer_argument(2));
    const std::uint32_t second = static_cast<std::uint32_t>(state.integer_argument(1));
    const std::uint32_t first = static_cast<std::uint32_t>(state.integer_argument(0));
    screen_factory_4250f0(1, first, second, third, 0, 0, 0);
    return 0;
}

} // namespace th20
