// Maintained whole-function source frontier for original 0x004818E0 Bullet
// emitter (3735B code + 97B original NOP and two native jump tables).
// NONEXACT: the actual original 935-instruction body plus 24 native switch
// table relocs still differ from this compiled C++20 candidate. Preserve
// authentic Bullet/shot/animation owners, not fabricated Renderer storage.
// The original source depended on a legacy MSVC STL specialization: its
// move conversion is a REAL noninlined 8B helper at 0x0040B280 and its
// shared_ptr move assignment a real 63B method at 0x0047C530. Both are
// reconstructed independently in ShotSharedPtrMoveLegacy.cpp under its
// distinct /GS- /sdl- profile. Forward declarations here preserve the
// original E8 call sequence without faking a game-owned trampoline.
// This is a pinned-library ABI overlay; final linked COMDAT/ODR selection
// and portable standard-library behavior remain unverified.
#include "ShotMetadata.hpp"
#include <memory>
#include <utility>
namespace std {
template <>
__declspec(noinline)
shared_ptr<EtamaArgInf>&& move<shared_ptr<EtamaArgInf>&>(shared_ptr<EtamaArgInf>&) noexcept;
template <>
shared_ptr<EtamaArgInf>&
shared_ptr<EtamaArgInf>::operator=(shared_ptr<EtamaArgInf>&&) noexcept;
}
#include "Bullet.hpp"
#include "BulletStyle.hpp"
#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "AnimationCallback.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "GameRandom.hpp"
#include "MotionMath.hpp"
#include "ScalarMath.hpp"
#include "Player.hpp"
#include "CollisionGeometry.hpp"
#include <cstdint>
#include <memory>
#include <utility>
#include <cmath>

namespace th20 {
extern GameRandom process_bullet_random;
extern const float native_zero, native_one, native_two;
extern const float native_pi, native_half, native_alternate_sign;
extern const float native_origin_z;

std::int32_t BulletController::emit(const ShotParameters& shot,
                                    std::shared_ptr<ShotMetadata> descriptor,
                                    int column, int row, float player_direction) {
    IntrusiveLink<Bullet>* free_link = free.front();
    if (free_link == nullptr) return 1;
    Bullet* bullet = free_link->node_value();
    bullet->link.detach();
    active.prepend(&bullet->link);
    ShotMetadata* metadata_source = descriptor.get();
    bullet->metadata = std::move(descriptor);
    bullet->select_context(view_index);
    float heading = 0.0f;
    bullet->timer_4d8 = native_one;
    bullet->timer_4e8 = native_one;

    float speed;
    // Original native +0x112..+0x16E tests rows > 1 before entering the
    // stepped-speed branch; under /Od the branch direction is visible.
    if (shot.rows > 1)
        speed = shot.speed - ((shot.speed-shot.speed_step)*static_cast<float>(row)) /
                (static_cast<float>(shot.rows)-native_one);
    else
        speed = shot.speed;
    bullet->field_24 = speed;
    const std::uint32_t mode = static_cast<std::uint16_t>(metadata_source->field_38);
    switch (mode) {
      case 0: case 1: {
        float angular;
        // Original +0x1AD checks odd count, executing the odd branch
        // FIRST; even parity jumps to the second branch at +0x1CD.
        // Do not reverse the logically equivalent branch under MSVC /Od.
        if (shot.count & 1)
            angular = static_cast<float>((column+1)/2) * shot.angle_step;
        else
            angular = static_cast<float>(column/2) * shot.angle_step + shot.angle_step*native_half;
        heading+=angular;
        if (column & 1) heading*=native_alternate_sign;
        if (mode==0) heading+=player_direction;
        heading+=shot.angle;
        break;
      }
      case 2: heading+=player_direction; [[fallthrough]];
      case 3:
        heading = static_cast<float>(row)*shot.angle_step + shot.angle +
             (static_cast<float>(column)*native_pi*native_two)/static_cast<float>(shot.count)+heading;
        break;
      case 4: heading+=player_direction; [[fallthrough]];
      case 5:
        heading = static_cast<float>(row)*shot.angle_step + shot.angle +
             (static_cast<float>(column)*native_pi*native_two)/static_cast<float>(shot.count) +
             native_pi/static_cast<float>(shot.count)+heading;
        break;
      case 6:
        heading = process_bullet_random.signed_range(shot.angle_step) + shot.angle;
        break;
      case 7:
        speed = process_bullet_random.range(shot.speed_step) + shot.speed;
        heading = static_cast<float>(row)*shot.angle_step + shot.angle +
             (static_cast<float>(column)*native_pi*native_two)/static_cast<float>(shot.count)+heading;
        break;
      case 8:
        heading = process_bullet_random.signed_range(shot.angle_step) + shot.angle;
        speed = process_bullet_random.range(shot.speed_step) + shot.speed;
        break;
      case 9: case 10:
        heading = (static_cast<float>(column)*native_pi*native_two)/static_cast<float>(shot.count);
        // Original +0x48A also executes ODD rows first and jumps to
        // the even branch at +0x4FE. Both paths retain their real
        // signed-half arithmetic and independent stepped-speed formula.
        if (shot.rows&1) {
           heading = static_cast<float>((row+1)/2)*shot.angle_step+heading;
           if (shot.rows>1)
             speed=(static_cast<float>((row+1)&~1)*(shot.speed_step-shot.speed)) /
                   static_cast<float>(shot.rows-1)+shot.speed;
        } else {
           heading = static_cast<float>(row/2)*shot.angle_step+shot.angle_step*native_half+heading;
           if (shot.rows>1)
             speed=(static_cast<float>(row&~1)*(shot.speed_step-shot.speed)) /
                   static_cast<float>(shot.rows-1)+shot.speed;
        }
        if (row&1)heading*=native_alternate_sign;
        if (mode==9)heading+=player_direction;
        heading+=shot.angle;
        break;
      case 11: {
        float circle_angle = (static_cast<float>(column)*native_pi*native_two)/static_cast<float>(shot.count);
        heading=circle_angle;
        const float a=scalar_math::cosine(circle_angle)*shot.speed;
        const float b=scalar_math::sine(circle_angle)*shot.speed_step;
        // Original 0x00481F45 and 0x00481F66 directly call the custom
        // game XY-norm and arctangent functions, NOT CRT hypot/atan2.
        speed=geometry::norm_xy(a,b);
        heading=scalar_math::arctangent(b,a)+shot.angle;
        break;
      }
      case 12: {
        float circle_angle=(static_cast<float>(column)*native_pi*native_two)/static_cast<float>(shot.count)+native_pi/static_cast<float>(shot.count);
        // Original +0x1FDD adds the previous heading, not an overwrite.
        heading+=circle_angle+shot.angle;
        // Original 0x00481FF2 sine -> 0x00481FFA absolute; omitting abs
        // changes the actual wave/amplitude for negative sine values.
        const float value=scalar_math::absolute(scalar_math::sine(circle_angle));
        speed=(native_one-value*shot.speed_step)*speed;
        break;
      }
    }
    bullet->speed=speed;
    bullet->angle=add_angles(heading,0.0f);
    bullet->position=shot.position;
    if (metadata_source->field_00!=0.0f) {
        Vector3 delta;
        polar(delta,static_cast<float>(bullet->angle),metadata_source->field_00);
        bullet->position.x += delta.x;
        bullet->position.y += delta.y;
    }
    bullet->position.z=native_origin_z;
    bullet->state=1;
    bullet->flags.bits|=1u;
    bullet->timer_4f8=0;
    bullet->timer_508=0;
    bullet->field_18=0;
    bullet->scale=native_one;
    bullet->interpolation_474.stop();
    polar(bullet->velocity,heading,speed);
    bullet->field_4e=static_cast<std::int16_t>(shot.color);
    bullet->field_4c=static_cast<std::int16_t>(shot.type);
    bullet->field_54=0;
    bullet->flags.bits&=~8u;
    bullet->flags.bits&=~4u;
    bullet->flags.bits|=2u;
    bullet->field_4d0=60;
    bullet->timer_4a0=0;
    bullet->timer_4b0=0;
    bullet->timer_4c0=0;
    bullet->field_4d4=3;

    bullet->animation=current_animation_pool->allocate_animation();
    // Original native +0x972 immediately E8-calls 0x004299D0 reset
    // on the newly returned pool Animation before binding its bullet owner.
    bullet->animation->reset();
    bullet->animation->user_data=bullet;
    bullet->animation->set_field_5e0(bullet_animation_script);
    // Original emitter E8 at 0x004822C5 goes to the 338B direct
    // script loader, not the distinct 32B bind_animation wrapper.
    // Original 0x00482297 separately calls 0x004856C0 to resolve script
    // by shot type; directly reading style.script lost this real E8.
    file->load_script(bullet->animation,type_to_script(shot.type));
    bullet->flags.bits|=0x10u;
    bullet->animation->base.flags.layer_mode=1;
    BulletStyle& style=bullet_styles[shot.type];
    if (style.child_script!=0) {
        // Original 0x00482310 calls Context::bullet_controller() (the
        // shared physical 0x0040C300 getter), then loads that owner's
        // +0x286D8C file for the child; not this controller's file.
        bullet->animation_handle=context->bullet_controller()->file->spawn(nullptr,style.child_script,bullet->position,0.0f,-1,nullptr);
    }
    bullet->style=&style;
    bullet->color=0xffd08080u;
    switch(style.cancel_type) {
      case 0: bullet->cancel_script=static_cast<int>(shot.color)*2+6;break;
      case 1: bullet->cancel_script=static_cast<int>(shot.color);break;
      case 2: bullet->cancel_script=-1;bullet->flags.bits|=0x10u;break;
      case 3: bullet->cancel_script=18;break;
      case 4: bullet->cancel_script=8;break;
      case 6:
        bullet->cancel_script=style.colors[shot.color].words[3];
        bullet->color=style.colors[shot.color].words[4];
        bullet->flags.bits|=0x10u;break;
      case 7: bullet->cancel_script=263;bullet->flags.bits|=0x10u;break;
      case 8: bullet->cancel_script=266;bullet->flags.bits|=0x10u;break;
      case 9: bullet->cancel_script=269;bullet->flags.bits|=0x10u;break;
      case 10: bullet->cancel_script=278;bullet->flags.bits|=0x10u;break;
    }
    bullet->flags.bits &= ~0x1800u;
    bullet->draw_group=style.draw_group;
    bullet->field_40=metadata_source->field_44;
    bullet->command_index=5;
    bullet->size.x=bullet_radius(static_cast<int>(shot.type));
    bullet->size.y=bullet->size.x;
    bullet->command_flags.bits=0;
    bullet->field_38=metadata_source->field_48;
    // Original out-of-range (0x004825A5) and non-opcode-1 (0x004825CD)
    // branches share ONE native interrupt(2) site at 0x004826AC,
    // not the two independent calls emitted by the previous nested if.
    if (bullet->field_38<metadata_source->commands.size() &&
        metadata_source->commands[bullet->field_38].opcode==1) {
            // Original native 0x004825EC and 0x0048261F make TWO
            // additional, separate pmr::vector::operator[] calls after
            // testing opcode at 0x004825C4. The opcode-1 operand at +0x10
            // is a genuine signed 16-bit ECL event ID (MOVSX WORD), not
            // the 32-bit view used for other BulletCommand opcodes.
            if (static_cast<std::int16_t>(metadata_source->commands[bullet->field_38].operand_10)!=1)
                bullet->animation->interrupt(
                    static_cast<std::int16_t>(metadata_source->commands[bullet->field_38].operand_10)+7);
            bullet->state=2;
            // Original 0x00482681 calls Vector3::operator-=, not +=:
            // native first-command advance moves back two velocity steps.
            bullet->position-=bullet->velocity*2.0f;
            ++bullet->field_38;
    } else bullet->animation->interrupt(2);
    bullet->run_extended_commands();
    bullet->animation->update();
    if (field_48>0.0f) {
        const auto& player_position=context->player()->position_ref();
        if (geometry::squared_distance_xy(bullet->position,player_position)<field_48) {
            bullet->deactivate();
            return -1;
        }
    }
    return 0;
}
} // namespace th20
