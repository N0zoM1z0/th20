#include "StageResource.hpp"

#include "AnimationRuntimeOwner.hpp"
#include "AnimationFile.hpp"
#include "Angle.hpp"
#include "Graphics.hpp"
#include "Matrix4.hpp"
#include "NativeGraphicsModeAction.hpp"
#include "NativeAnimationResetHooksView.hpp"

#include <d3dx9math.h>
#include <cstddef>
#include <cstdint>

namespace th20 {

extern const float native_zero_56e0e8;

std::int32_t __fastcall graphics_enable_fog(Graphics* graphics);
std::int32_t __fastcall graphics_disable_fog(Graphics* graphics);
std::int32_t __fastcall graphics_enable_depth_writes(Graphics* graphics);
std::int32_t __fastcall graphics_disable_depth_writes(Graphics* graphics);
StageResourcePrimitiveTransform* __cdecl advance_stage_resource_primitive(
    StageResourcePrimitiveTransform* primitive, std::int32_t size) {
    return reinterpret_cast<StageResourcePrimitiveTransform*>(
        reinterpret_cast<std::byte*>(primitive) + size);
}

std::int32_t StageResourceOwner::draw_objects_for_layer(std::int32_t layer) {
    struct DrawCursor {
        StageResourcePrimitiveTransform* primitive;
        StageResourceInstanceRecord* instance;
    } cursor;
    cursor.instance = static_cast<StageResourceInstanceRecord*>(instances);
    std::uint32_t depth_write_state = 1;
    script_state.draw_inline_animations_for_layer(layer);

    current_animation_pool->flush_draws();
    graphics_enable_fog(&process_graphics);
    reinterpret_cast<NativeGraphicsModeAction&>(process_graphics)
        .select_view_477520(3);
    reinterpret_cast<NativeAnimationResetHooks*>(current_animation_pool)
        ->set_draw_mode_477770(1);

    while (cursor.instance->object_index >= 0) {
        StageResourceObjectRecord& object =
            *static_cast<StageResourceObjectRecord**>(objects)[cursor.instance->object_index];
        if (static_cast<std::int8_t>(object.layer) != layer)
            goto next_instance;

        {
            const Vector3 instance_offset(cursor.instance->position.x,
                                          cursor.instance->position.y,
                                          cursor.instance->position.z);
            if (object.is_outside_viewport(
                    instance_offset,
                    *reinterpret_cast<const float*>(
                        reinterpret_cast<const std::uint8_t*>(this) + 0x32c4),
                    process_graphics.viewports[3]) != 0) {
                ++render_counts.culled_objects;
                *reinterpret_cast<std::uint16_t*>(
                    reinterpret_cast<std::byte*>(cursor.instance) + 2) &= 0xfffeu;
                goto next_instance;
            }

            *reinterpret_cast<std::int8_t*>(
                reinterpret_cast<std::byte*>(&object) + 3) |= 2;
            cursor.primitive = reinterpret_cast<StageResourcePrimitiveTransform*>(
                reinterpret_cast<std::byte*>(&object) + sizeof(object));
            while (cursor.primitive->header.type >= 0) {
                Animation* animation = primitive_animations +
                    cursor.primitive->header.animation_index;
                switch (cursor.primitive->header.type) {
                case 0:
                float original_rotation;
                original_rotation = animation->rotation_y_value();
                if (animation->base.flags.bytes_00.animation_mode >= 4) {
                    D3DXVECTOR3 local_position;
                    local_position.x = cursor.primitive->position_x;
                    local_position.y = cursor.primitive->position_y;
                    local_position.z = cursor.primitive->position_z;

                    if (*reinterpret_cast<const float*>(
                            reinterpret_cast<const std::byte*>(&object) + 0x0c) !=
                        native_zero_56e0e8) {
                        D3DXMATRIX rotation;
                        D3DXVECTOR3 transformed_position;
                        matrix_identity(reinterpret_cast<Matrix4*>(&rotation));
                        D3DXMatrixRotationY(&rotation,
                            *reinterpret_cast<const float*>(
                                reinterpret_cast<const std::byte*>(&object) + 0x0c));
                        D3DXVec3TransformCoord(&transformed_position,
                                               &local_position, &rotation);
                        local_position = transformed_position;
                        animation->set_rotation_y_forward(normalize_angle(
                            original_rotation + *reinterpret_cast<const float*>(
                                reinterpret_cast<const std::byte*>(&object) + 0x0c)));
                    }

                    animation->vector_5bc.x =
                        local_position.x + cursor.instance->position.x;
                    animation->vector_5bc.y =
                        local_position.y + cursor.instance->position.y;
                    animation->vector_5bc.z =
                        local_position.z + cursor.instance->position.z;

                    if (cursor.primitive->scale_x != native_zero_56e0e8) {
                        animation->set_scale_x(cursor.primitive->scale_x /
                            animation->sprite_data()->extent_4c);
                    }
                    if (cursor.primitive->scale_y != native_zero_56e0e8) {
                        animation->set_scale_y(cursor.primitive->scale_y /
                            animation->sprite_data()->extent_48);
                    }
                }

                if (animation->base.flags.bytes_00.animation_mode == 8 ||
                    animation->base.flags.bytes_00.animation_mode == 24) {
                    graphics_enable_fog(&process_graphics);
                } else {
                    graphics_disable_fog(&process_graphics);
                }

                if (((animation->base.flags.word_04 >> 4) & 1u) != 0) {
                    graphics_disable_depth_writes(&process_graphics);
                    depth_write_state = 0;
                } else {
                    graphics_enable_depth_writes(&process_graphics);
                    depth_write_state = 1;
                }

                current_animation_pool->draw(animation);
                animation->set_rotation_y_forward(original_rotation);
                ++render_counts.primitive_draws;
                    break;
                default:
                    goto advance_primitive;
                }
advance_primitive:
                cursor.primitive = advance_stage_resource_primitive(
                    cursor.primitive, cursor.primitive->header.size);
            }

            *reinterpret_cast<std::uint16_t*>(
                reinterpret_cast<std::byte*>(cursor.instance) + 2) |= 1u;
            ++render_counts.visible_objects;
        }

next_instance:
        ++cursor.instance;
    }

    graphics_disable_depth_writes(&process_graphics);
    reinterpret_cast<NativeAnimationResetHooks*>(current_animation_pool)
        ->reset_after_stage_draw_4750a0();
    current_animation_pool->flush_draws();
    return 0;
}

} // namespace th20
