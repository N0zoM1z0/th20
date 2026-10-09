#include "Graphics.hpp"
#include "AnimationFile.hpp"
#include "Animation.hpp"
#include "SpriteVertices.hpp"
namespace th20 {
AnimationHandle Graphics::create_grid_strip(std::int32_t rows,std::int32_t script) {
    AnimationHandle handle=process_graphics.surface_animation->spawn(nullptr,script,41,nullptr);
    Animation* animation=handle.resolve();
    animation->allocate_geometry(sizeof(SpriteTexturedVertex)*rows*2);
    if (rows>2) {
        animation->base.flags.bytes_00.field_00=12;
        animation->base.flags.byte_08=static_cast<std::uint8_t>(animation->base.flags.byte_08|0x30);
        animation->variables().field_00=rows;
        auto* vertex=animation->mesh_vertices();
        for (std::int32_t i=0;i<rows*2;++i) {
            vertex->position.z=0.0f;vertex->reciprocal_w=1.0f;
            vertex->color=0xffffffffu;++vertex;
        }
    } else animation->base.flags.bytes_00.field_00=0;
    return handle;
}
AnimationHandle Graphics::create_surface_strip(std::int32_t rows,std::int32_t script) {
    AnimationHandle handle=process_graphics.surface_animation->spawn(nullptr,script,42,nullptr);
    Animation* animation=handle.resolve();
    animation->allocate_geometry(sizeof(SpriteTexturedVertex)*rows*2);
    if (rows>2) {
        animation->base.flags.bytes_00.field_00=12;
        animation->variables().field_00=rows;
        auto* vertex=animation->mesh_vertices();
        for (std::int32_t i=0;i<rows*2;++i) {
            vertex->position.z=0.0f;vertex->reciprocal_w=1.0f;
            vertex->color=0xffffffffu;++vertex;
        }
    } else animation->base.flags.bytes_00.field_00=0;
    return handle;
}
} // namespace th20
