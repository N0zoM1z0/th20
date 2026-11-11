// Original session-indexed EffectInfo selector used by particle and effect
// creation. The returned owner is borrowed from the current game Session.
#include "Session.hpp"

namespace th20 {
EffectInfo* __cdecl particle_effect_info_for_session_437520(std::int32_t index) {
    return session.context(index).effect_info();
}
}
