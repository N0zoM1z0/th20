#include "Animation.hpp"
#include "BulletStyle.hpp"
#include "LaserParameters.hpp"

namespace th20 {

std::int32_t laser_infinite_animation_script_callback(Animation* animation,
                                                       std::int32_t parameter) {
    auto* laser=static_cast<Laser*>(animation->user_data);
    if (static_cast<std::int32_t>(
            bullet_styles[laser->field_6e4].colors[0].words[0])>=0) {
        return static_cast<std::int32_t>(
            bullet_styles[laser->field_6e4].colors[laser->field_6e8].words[parameter]);
    } else {
        return parameter;
    }
}

} // namespace th20
