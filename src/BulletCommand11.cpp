// Entire original Bullet command-11 edge-ray state machine.
// Original native MSVC /Od code initializes two 32-bit scalar screen bounds
// after polar2; the initializations survive in the original even though
// their local stack slots are not subsequently loaded. Preserve the actual
// native local writes, not arbitrary padding or dead invented instructions.
#include "Bullet.hpp"
#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "BulletWrapBounds.hpp"
#include "BulletCommand11Geometry.hpp"
#include "BulletRayMath.hpp"

namespace th20 {
extern const float native_minus_384, native_minus_448, native_384, native_448;
extern const float native_one, native_two, native_zero;
extern const float native_minus_998, native_minus_999;

// This Vector2-based XY polar call shares the observed native 0x00439330
// entry with the existing Vector3 polar method. Native alias linkage remains
// unresolved; the pointer ABI and two written lanes are independently observed.
void polar2(Vector2& result, float angle, float length);

std::int32_t Bullet::advance_command11() {
    commands.at(11).timer--;
    if (commands.at(11).word_30 != 0) {
        const float height = animation->sprite_data()->extent_48;
        const float width = animation->sprite_data()->extent_4c;
        if (bullet_wrap_outside(position, width, height)) {
            Vector2 corner;
            Vector2 direction;
            float crossed[4]{};
            float projected[4]{};
            polar2(direction, static_cast<float>(angle), 1.0f);
            // Original +0x105..+0x11E performs four real instructions:
            // load original 384.0f / 448.0f and initialize distinct local
            // stack slots -0x78 / -0x7C. No later instructions read them;
            // the original source-level scalar initializations survive /Od.
            const float screen_half_width = native_384;
            const float screen_half_height = native_448;

            corner.x = (native_minus_384 - animation->sprite_data()->extent_4c) / native_two - position.x;
            corner.y = (native_448 / native_two + (native_minus_448 - animation->sprite_data()->extent_48) / native_two) - position.y;
            normalize_vector2(corner,corner);
            crossed[0] = cross_components(direction,corner);
            projected[0] = dot_components(direction,corner);

            corner.x = (native_384 + animation->sprite_data()->extent_4c) / native_two - position.x;
            corner.y = (native_448 / native_two + (native_minus_448 - animation->sprite_data()->extent_48) / native_two) - position.y;
            normalize_vector2(corner,corner);
            crossed[1] = cross_components(direction,corner);
            projected[1] = dot_components(direction,corner);

            corner.x = (native_minus_384 - animation->sprite_data()->extent_4c) / native_two - position.x;
            corner.y = (native_448 / native_two + (native_448 + animation->sprite_data()->extent_48) / native_two) - position.y;
            normalize_vector2(corner,corner);
            crossed[2] = cross_components(direction,corner);
            projected[2] = dot_components(direction,corner);

            corner.x = (native_384 + animation->sprite_data()->extent_4c) / native_two - position.x;
            corner.y = (native_448 / native_two + (native_448 + animation->sprite_data()->extent_48) / native_two) - position.y;
            normalize_vector2(corner,corner);
            crossed[3] = cross_components(direction,corner);
            projected[3] = dot_components(direction,corner);

            float last_negative = native_minus_999;
            for (std::int32_t i = 0; i < 4; ++i) {
                if (crossed[i] <= 0.0f &&
                    last_negative < projected[i] &&
                    native_zero <= projected[i]) {
                    last_negative = projected[i];
                }
            }
            float last_positive = native_minus_999;
            for (std::int32_t i = 0; i < 4; ++i) {
                if (native_zero <= crossed[i] &&
                    last_positive < projected[i] &&
                    native_zero <= projected[i]) {
                    last_positive = projected[i];
                }
            }
            if (last_negative < native_minus_998 || last_positive < native_minus_998) {
                command_flags.words.low &= ~0x100u;
                return 1;
            }
        }
    }
    if (commands.at(11).timer.at_most(0)) {
        command_flags.words.low &= ~0x100u;
        return 1;
    }
    return 0;
}
}
