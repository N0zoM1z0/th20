#include "BulletStyle.hpp"

namespace th20 {

// Kept in its own translation unit because the native accessor's exception
// profile differs from the neighboring unchecked BulletStyle field readers.
BulletStyle* bullet_style(std::int32_t type) {
    return &bullet_styles[type];
}

} // namespace th20
