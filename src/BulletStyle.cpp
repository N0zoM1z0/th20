#include "BulletStyle.hpp"

namespace th20 {

float bullet_radius(std::int32_t type) {
    return bullet_styles[type].radius;
}

} // namespace th20
