#include "BulletStyle.hpp"

namespace th20 {

float bullet_radius(std::int32_t type) {
    return bullet_styles[type].radius;
}
// Original PE reads the first 32-bit word of each 0x158-byte style record.
std::int32_t type_to_script(std::int32_t type) {
    return static_cast<std::int32_t>(bullet_styles[type].script);
}

} // namespace th20
