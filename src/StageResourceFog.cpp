#include "StageResource.hpp"
#include "AnimationFile.hpp"

namespace th20 {

AnimationFile* StageResourceOwner::animation_file() {
    return animation_file_value;
}

void StageBackgroundFogOwner::set_fog(std::int32_t duration,
                                      std::int32_t mode,
                                      const FogValue& target) {
    fog_interpolation.set_duration(duration);
    (void)fog_interpolation.set_mode(mode);
    fog_interpolation.set_start(current_fog);
    fog_interpolation.set_end(target);
    fog_interpolation.reset_timer();
}

void StageResourceOwner::set_fog(std::int32_t duration,
                                  std::int32_t mode,
                                  const FogValue& target) {
    background.set_fog(duration, mode, target);
}

} // namespace th20
