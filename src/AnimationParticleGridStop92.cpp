#include "NativeParticleGridGroup.hpp"
#include "Animation.hpp"
namespace th20 {
std::int32_t NativeParticleGridGroup::slot_0c() {
    for (std::int32_t index=0; index<200; ++index) {
        Animation* const resolved=colors_08[index].resolve();
        if (!resolved) continue;
        resolved->stop();
    }
    return 0;
}
}
