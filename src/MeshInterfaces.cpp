#include "RenderMesh.hpp"
#include "Animation.hpp"
#include "EnemyState.hpp"
#include "WindowState.hpp"

namespace th20 {
std::int32_t WindowState::mesh_view_x(std::int32_t index) const { return mesh_offset_x[index]; }
std::int32_t WindowState::mesh_view_y(std::int32_t index) const { return mesh_offset_y[index]; }
std::int32_t WindowState::mesh_width() const { return scaled_width; }
std::int32_t WindowState::mesh_height() const { return scaled_height; }
SpriteTexturedVertex* Animation::mesh_vertices() { return static_cast<SpriteTexturedVertex*>(geometry); }
Vector3& EnemyState::position_ref() { return motion_110.position_ref(); }
Angle& Angle::operator-=(float input) { value=normalize_angle(value-input);return *this; }
float squared_norm_xy(const Vector3& value) { return value.x*value.x+value.y*value.y; }
} // namespace th20
