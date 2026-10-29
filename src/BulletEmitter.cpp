// Maintained whole-function source frontier for original 0x004818E0 Bullet
// emitter (3735B code + 97B original NOP and two native jump tables).
// NONEXACT: the actual original 935-instruction body plus 24 native switch
// table relocs still differ from this compiled C++20 candidate. Preserve
// authentic Bullet/shot/animation owners, not fabricated Renderer storage.
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
extern std::int32_t type_to_script(std::int32_t type);

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
        if ((shot.count & 1) == 0)
            angular = static_cast<float>(column/2) * shot.angle_step + shot.angle_step*native_half;
        else
            angular = static_cast<float>((column+1)/2) * shot.angle_step;
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
        if (!(shot.rows&1)) {
           heading = static_cast<float>(row/2)*shot.angle_step+shot.angle_step*native_half+heading;
           if (shot.rows>1)
             speed=(static_cast<float>(row&~1)*(shot.speed_step-shot.speed)) /
                   static_cast<float>(shot.rows-1)+shot.speed;
        } else {
           heading = static_cast<float>((row+1)/2)*shot.angle_step+heading;
           if (shot.rows>1)
             speed=(static_cast<float>((row+1)&~1)*(shot.speed_step-shot.speed)) /
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
        speed=std::hypot(a,b);
        heading=std::atan2(b,a)+shot.angle;
        break;
      }
      case 12: {
        float circle_angle=(static_cast<float>(column)*native_pi*native_two)/static_cast<float>(shot.count)+native_pi/static_cast<float>(shot.count);
        heading=circle_angle+shot.angle;
        const float value=scalar_math::sine(circle_angle);
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
    bullet->animation->user_data=bullet;
    bullet->animation->set_field_5e0(bullet_animation_script);
    file->bind_animation(bullet->animation,bullet_styles[shot.type].script);
    bullet->flags.bits|=0x10u;
    bullet->animation->base.flags.layer_mode=1;
    BulletStyle& style=bullet_styles[shot.type];
    if (style.child_script!=0) {
        bullet->animation_handle=file->spawn(nullptr,style.child_script,bullet->position,0.0f,-1,nullptr);
    }
    bullet->style=&style;
    bullet->color.value=0xffd08080u;
    switch(style.cancel_type) {
      case 0: bullet->cancel_script=static_cast<int>(shot.color)*2+6;break;
      case 1: bullet->cancel_script=static_cast<int>(shot.color);break;
      case 2: bullet->cancel_script=-1;bullet->flags.bits|=0x10u;break;
      case 3: bullet->cancel_script=18;break;
      case 4: bullet->cancel_script=8;break;
      case 6:
        bullet->cancel_script=style.colors[shot.color].words[3];
        bullet->color.value=style.colors[shot.color].words[4];
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
    if (bullet->field_38<metadata_source->commands.size()) {
        if (metadata_source->commands[bullet->field_38].opcode==1) {
            const BulletCommand& command=metadata_source->commands[bullet->field_38];
            if (command.operand_10!=1)
                bullet->animation->interrupt(command.operand_10+7);
            bullet->state=2;
            bullet->position+=bullet->velocity*2.0f;
            ++bullet->field_38;
        } else bullet->animation->interrupt(2);
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
