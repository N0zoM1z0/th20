#include "RenderMesh.hpp"
#include "Animation.hpp"
#include "Graphics.hpp"
#include "WindowState.hpp"
#include "DiagnosticAllocator.hpp"
#include <cstring>
namespace th20 {
RenderMesh::RenderMesh(std::int32_t num_columns,std::int32_t num_rows,
                       std::int32_t surface,std::int32_t view)
    :columns(0),rows(0),root(),strip_handles(nullptr),strips(nullptr),
     vertices(nullptr),positions(nullptr),view_index(0),context(nullptr) {
    if (!process_graphics.resource_19c) {
        std::memset(static_cast<void*>(this),0,sizeof(*this));
        return;
    }
    select_context(view);
    columns=num_columns;rows=num_rows;
    strip_handles=static_cast<AnimationHandle*>(process_allocator->allocate_bytes(
        sizeof(AnimationHandle)*num_columns-1,"D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\effect.cpp:430 SprtID"));
    strips=static_cast<Animation**>(process_allocator->allocate_bytes(
        sizeof(Animation*)*num_columns-1,"D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\effect.cpp:431 SprtInf*"));
    vertices=static_cast<SpriteTexturedVertex*>(process_allocator->allocate_bytes(
        sizeof(SpriteTexturedVertex)*num_columns*num_rows,"D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\effect.cpp:432 sprtVERTEXC"));
    positions=static_cast<Vector3*>(process_allocator->allocate_bytes(
        sizeof(Vector3)*num_columns*num_rows,"D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\effect.cpp:433 FVector"));
    if (!surface) {
        root=process_graphics.create_grid_strip(2,0);
        Animation* animation=root.resolve();
        animation->user_data=this;
        animation->clear_flag0_recursively();
        for (std::int32_t column=0;column<columns-1;++column) {
            Animation* animation=(strip_handles[column]=process_graphics.create_grid_strip(num_rows,0)).resolve();
            strips[column]=animation;
            strips[column]->base.flags.bytes_00.field_01=0;
            strips[column]->base.flags.layer_mode=0;
        }
    } else {
        std::int32_t script=window_state.scaled_width==640?13:
            window_state.scaled_width==960?14:15;
        root=process_graphics.create_surface_strip(2,script);
        Animation* animation=root.resolve();
        animation->user_data=this;
        animation->clear_flag0_recursively();
        animation->set_layer(27);
        for (std::int32_t column=0;column<columns-1;++column) {
            Animation* animation=(strip_handles[column]=process_graphics.create_surface_strip(num_rows,script)).resolve();
            strips[column]=animation;
            strips[column]->base.flags.bytes_00.field_01=0;
            strips[column]->base.flags.layer_mode=0;
            Animation* strip=strips[column];
            strip->set_layer(27);
        }
    }
}
RenderMesh::~RenderMesh() {
    root.retire();
    TH20_RELEASE_BYTES_AND_RESET(vertices);
    TH20_RELEASE_BYTES_AND_RESET(positions);
    for (std::int32_t column=0;column<columns-1;++column) strip_handles[column].retire();
    TH20_RELEASE_BYTES_AND_RESET(strip_handles);
    TH20_RELEASE_BYTES_AND_RESET(strips);
}
} // namespace th20
