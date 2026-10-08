#include "RenderMesh.hpp"
#include "EnemyState.hpp"
#include "WindowState.hpp"
#include "ClockScalar.hpp"
#include "MotionMath.hpp"
#include "ScalarMath.hpp"

namespace th20 {
namespace { constexpr float pi=3.1415927410125732f; }
EnemyMeshOwner::EnemyMeshOwner():mesh(nullptr),field_04(0),radius(0.0f),current_radius(0.0f),color(0),phase_x(),phase_y() {}
void EnemyState::update_mesh() {
    if (mesh) {
        auto* point=mesh->mesh->positions;
        Vector3 center,delta;
        float radius=mesh->current_radius;
        Angle phase_x=mesh->phase_x,phase_y=mesh->phase_y;
        const float strength=8.0f;
        if (mesh->current_radius<mesh->radius)
            mesh->current_radius=mesh->current_radius+float(default_timer_clock)*2.0f;
        center=position_ref();
        mesh->mesh->initialize((center.x-radius)-20.0f,(center.y-radius)-20.0f,
                               radius*2.0f+40.0f,radius*2.0f+40.0f);
        center.x=float(window_state.mesh_view_x(field_2e8))+center.x;
        center.y=float(window_state.mesh_view_y(field_2e8))+center.y;
        auto* vertex=mesh->mesh->vertices;
        for (std::int32_t column=0;column<mesh->mesh->columns;++column) {
            for (std::int32_t row=0;row<mesh->mesh->rows;++row) {
                delta=*point-center;
                float weight=radius*radius-squared_norm_xy(delta);
                if (weight>=0.0f) {
                    weight=weight/(radius*radius);
                    vertex->color=mesh->color;
                    vertex->channels.red=static_cast<std::uint8_t>(int(255.0f-float(255-vertex->channels.red)*weight));
                    vertex->channels.green=static_cast<std::uint8_t>(int(255.0f-float(255-vertex->channels.green)*weight));
                    vertex->channels.blue=static_cast<std::uint8_t>(int(255.0f-float(255-vertex->channels.blue)*weight));
                    vertex->channels.alpha=255;
                    normalize_to_length(delta,delta,weight*32.0f);
                    delta.x=scalar_math::sine(phase_x)*weight*strength+delta.x;
                    delta.y=scalar_math::sine(phase_y)*weight*strength+delta.y;
                    vertex->position+=delta;
                    vertex->position.z=0.0f;point->z=0.0f;
                } else vertex->channels.alpha=0;
                phase_x+=pi/32.0f;
                phase_y-=pi/64.0f;
                if (point->x<=0.0f) vertex->position.x=point->x=1.0f;
                else if (point->x>=float(window_state.scaled_width))
                    vertex->position.x=point->x=float(window_state.scaled_width)-1.0f;
                if (point->y<=0.0f) vertex->position.y=point->y=1.0f;
                else if (point->y>=float(window_state.scaled_height))
                    vertex->position.y=point->y=float(window_state.scaled_height)-1.0f;
                render_mesh_uv(*point,vertex->u,vertex->v);
                ++point;++vertex;
            }
        }
        mesh->phase_x+=(pi/16.0f)*float(default_timer_clock);
        mesh->phase_y+=(pi/32.0f)*float(default_timer_clock);
        mesh->mesh->update_strips();
    }
}
} // namespace th20
