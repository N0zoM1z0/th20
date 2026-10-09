#include "RenderMesh.hpp"
#include "Graphics.hpp"

namespace th20 {
void RenderMesh::initialize_surface_grid(float x,float y,float width,float height) {
    if (!columns) return;
    Vector3 position(x,y,0.0f);
    float step_x=width/(float(columns)-1.0f);
    float step_y=height/(float(rows)-1.0f);
    auto* vertex=vertices;
    auto* point=positions;
    for (std::int32_t column=0;column<columns;++column) {
        position.y=y;
        for (std::int32_t row=0;row<rows;++row) {
            *point=position;
            vertex->position=*point;
            render_mesh_uv(*point,vertex->u,vertex->v);
            vertex->position.x+=float(process_graphics.viewports[2].offset_x);
            vertex->position.y+=float(process_graphics.viewports[2].offset_y);
            vertex->reciprocal_w=1.0f;
            vertex->color=0xffffffffu;
            position.y+=step_y;
            ++point;++vertex;
        }
        position.x+=step_x;
    }
    update_strips();
}
} // namespace th20
