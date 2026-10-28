// Whole original 781-byte Bullet screen-wrap boss. Four direction-specific
// mirrors use the real SpriteData extents and converge at one native shared
// hit-processing branch. Keep compiler-observed short-circuit/goto structure.
#include "Bullet.hpp"
#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "BulletWrapBounds.hpp"
#include "SoundInf.hpp"
namespace th20 {
extern const float native_448,native_384,native_minus_384,native_two;
std::int32_t Bullet::wrap_screen() {
    std::int32_t hit=0;
    const float height=animation->sprite_data()->extent_48;
    const float width=animation->sprite_data()->extent_4c;
    if (bullet_wrap_outside(position,width,height)) {
        if ((commands.at(6).word_38 & 1) && static_cast<double>(position.y)<0.0) {
            float extent=native_448 + animation->sprite_data()->extent_48;
            float old=position.y;
            position.y=old+extent;
            hit=1;
            goto wrapped;
}
        if ((commands.at(6).word_38 & 2) && position.y>native_448) {
            float extent=native_448+animation->sprite_data()->extent_48;
            float old=position.y;
            position.y=old-extent;
            hit=1;
            goto wrapped;
}
        if ((commands.at(6).word_38 & 4) && position.x<native_minus_384/native_two) {
            float extent=native_384+animation->sprite_data()->extent_4c;
            float old=position.x;
            position.x=old+extent;
            hit=1;
            goto wrapped;
}
        if ((commands.at(6).word_38 & 8) && position.x>native_384/native_two) {
            float extent=native_384+animation->sprite_data()->extent_4c;
            float old=position.x;
            position.x=old-extent;
            hit=1;
            goto wrapped;
        }
        if(hit) {
wrapped:
            ++commands.at(6).word_30;
            if (static_cast<std::int32_t>(field_40)>=0) process_sound.request_effect(field_40,0);
            if (static_cast<std::int32_t>(commands.at(6).word_30)>=static_cast<std::int32_t>(commands.at(6).word_34)) {
                command_flags.words.low &= ~0x1000u;
                return 1;
            }
        }
    }
    return 0;
}
}
