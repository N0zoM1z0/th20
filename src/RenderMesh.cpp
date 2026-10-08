#include "RenderMesh.hpp"
#include "Animation.hpp"
#include "Session.hpp"
#include "WindowState.hpp"

namespace th20 {
void RenderMesh::select_context(std::int32_t index) {
    view_index=index;
    context=&session.context(view_index);
}
void RenderMesh::initialize(float x,float y,float width,float height) {
    if (!columns) return;
    Vector3 position(float(window_state.mesh_view_x(view_index))+x,
                     float(window_state.mesh_view_y(view_index))+y,0.0f);
    float step_x=width/(float(columns)-1.0f);
    float step_y=height/(float(rows)-1.0f);
    auto* vertex=vertices;
    auto* point=positions;
    for (std::int32_t column=0;column<columns;++column) {
        for (std::int32_t row=0;row<rows;++row) {
            *point=position;
            vertex->position=*point;
            render_mesh_uv(*point,vertex->u,vertex->v);
            vertex->reciprocal_w=1.0f;
            vertex->color=0xffffffffu;
            position.y+=step_y;
            ++point;++vertex;
        }
        position.y=float(window_state.mesh_view_y(view_index))+y;
        position.x+=step_x;
    }
    update_strips();
}
void RenderMesh::update_strips() {
    if (!columns) return;
    auto* source=vertices;
    for (std::int32_t column=0;column<columns-1;++column) {
        auto* destination=strips[column]->mesh_vertices();
        for (std::int32_t row=0;row<rows;++row) {
            *destination=source[0];++destination;
            *destination=source[rows];++destination;
            ++source;
        }
    }
}
void render_mesh_uv(Vector3 position,float& u,float& v) {
    u=position.x/float(window_state.mesh_width());
    v=position.y/float(window_state.mesh_height());
    if (u<0.0f) u=0.0f;
    if (v<0.0f) v=0.0f;
}
} // namespace th20
