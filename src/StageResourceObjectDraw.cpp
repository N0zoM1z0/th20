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
    enum class DepthWriteState : std::int32_t {
        disabled = 0,
        enabled = 1,
    };

    auto* instance = instances;
    // The original /Od body writes this local at each depth transition but never reads it.
    DepthWriteState depth_write_state = DepthWriteState::enabled;
    script_state.draw_inline_animations_for_layer(layer);

    current_animation_pool->flush_draws();
    graphics_enable_fog(&process_graphics);
    reinterpret_cast<NativeGraphicsModeAction&>(process_graphics)
        .select_view_477520(3);
    current_animation_pool->set_draw_mode_477770(1);

    while (instance->object_index >= 0) {
        StageResourceObjectRecord& object =
            *objects[instance->object_index];
        if (object.layer != layer)
            goto next_instance;

        {
            const Vector3 instance_offset(instance->position.x,
                                          instance->position.y,
                                          instance->position.z);
            if (object.is_outside_viewport(
                    instance_offset,
                    script_state.scalars.cull_distance_squared,
                    process_graphics.viewports[3]) != 0) {
                ++render_counts.culled_objects;
                instance->visibility.visible = 0;
                goto next_instance;
            }

            object.flags |= StageResourceObjectRecord::passed_viewport_cull_mask;
            // The serialized primitive stream begins immediately after the 0x30-byte object.
            auto* primitive = reinterpret_cast<StageResourcePrimitiveTransform*>(
                reinterpret_cast<std::byte*>(&object) + sizeof(object));
            while (primitive->header.type >= 0) {
                Animation* animation = primitive_animations +
                    primitive->header.animation_index;
                switch (static_cast<StageResourcePrimitiveKind>(primitive->header.type)) {
                case StageResourcePrimitiveKind::animation_transform: {
                    const float original_rotation = animation->rotation_y_value();
                    if (animation->base.flags.bytes_00.animation_mode >= 4) {
                        D3DXVECTOR3 local_position;
                        D3DXMATRIX rotation;
                        local_position.x = primitive->position.x;
                        local_position.y = primitive->position.y;
                        local_position.z = primitive->position.z;

                        if (object.parameters.rotation_y !=
                            native_zero_56e0e8) {
                            D3DXVECTOR3 transformed_position;
                            matrix_identity(reinterpret_cast<Matrix4*>(&rotation));
                            D3DXMatrixRotationY(&rotation,
                                object.parameters.rotation_y);
                            D3DXVec3TransformCoord(&transformed_position,
                                                   &local_position, &rotation);
                            local_position = transformed_position;
                            animation->set_rotation_y_forward(normalize_angle(
                                original_rotation + object.parameters.rotation_y));
                        }

                        animation->vector_5bc.x =
                            local_position.x + instance->position.x;
                        animation->vector_5bc.y =
                            local_position.y + instance->position.y;
                        animation->vector_5bc.z =
                            local_position.z + instance->position.z;

                        if (primitive->scale_x != native_zero_56e0e8) {
                            animation->set_scale_x(primitive->scale_x /
                                animation->sprite_data()->extent_4c);
                        }
                        if (primitive->scale_y != native_zero_56e0e8) {
                            animation->set_scale_y(primitive->scale_y /
                                animation->sprite_data()->extent_48);
                        }
                    }

                    if (animation->base.flags.bytes_00.animation_mode == 8 ||
                        animation->base.flags.bytes_00.animation_mode == 24) {
                        graphics_enable_fog(&process_graphics);
                    } else {
                        graphics_disable_fog(&process_graphics);
                    }

                    if (animation->base.flags.bits_04.depth_write_disabled != 0) {
                        graphics_disable_depth_writes(&process_graphics);
                        depth_write_state = DepthWriteState::disabled;
                    } else {
                        graphics_enable_depth_writes(&process_graphics);
                        depth_write_state = DepthWriteState::enabled;
                    }

                    current_animation_pool->draw(animation);
                    animation->set_rotation_y_forward(original_rotation);
                    ++render_counts.primitive_draws;
                    break;
                }
                default:
                    break;
                }
                primitive = advance_stage_resource_primitive(
                    primitive, primitive->header.size);
            }

            instance->visibility.visible = 1;
            ++render_counts.visible_objects;
        }

// Native shared edge for layer mismatch and viewport-cull exits.
next_instance:
        ++instance;
    }

    graphics_disable_depth_writes(&process_graphics);
    current_animation_pool->reset_after_stage_draw_4750a0();
    current_animation_pool->flush_draws();
    return 0;
}

} // namespace th20
