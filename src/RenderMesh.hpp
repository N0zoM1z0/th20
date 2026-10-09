#pragma once
#include "AnimationHandle.hpp"
#include "Angle.hpp"
#include "SpriteVertices.hpp"
#include <cstddef>
#include <cstdint>

namespace th20 {
struct Animation;
struct Context;

// Native constructor, allocation widths and grid/strip consumers establish all
// nine words. Renderer allocation, deletion and publication remain dependencies.
struct RenderMesh {
    std::int32_t columns, rows;
    AnimationHandle root;
    AnimationHandle* strip_handles;
    Animation** strips;
    SpriteTexturedVertex* vertices;
    Vector3* positions;
    std::int32_t view_index;
    Context* context;
    RenderMesh(std::int32_t columns,std::int32_t rows,std::int32_t surface,std::int32_t view);
    ~RenderMesh();
    void select_context(std::int32_t index);
    void initialize(float x,float y,float width,float height);
    void initialize_surface_grid(float x,float y,float width,float height);
    void update_strips();
};
struct EnemyMeshOwner {
    RenderMesh* mesh;
    std::uint32_t field_04;
    float radius,current_radius;
    std::uint32_t color;
    Angle phase_x,phase_y;
    EnemyMeshOwner();
};
// Native cdecl passes all three coordinates by value; z is not consumed.
void render_mesh_uv(Vector3 position,float& u,float& v);
float squared_norm_xy(const Vector3& value);
#if defined(_M_IX86)
static_assert(sizeof(RenderMesh)==0x24);
static_assert(offsetof(RenderMesh,positions)==0x18);
static_assert(sizeof(EnemyMeshOwner)==0x1c);
static_assert(offsetof(EnemyMeshOwner,phase_x)==0x14);
#endif
} // namespace th20
