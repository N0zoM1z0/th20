#include "StageResource.hpp"
#include "StageResourceObjectVisibility.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace th20 {

extern const float native_zero_56e0e8;
extern const float native_one_56c8cc;
extern const float native_cull_screen_width_56cdac;
extern const float native_cull_screen_height_56cda8;
extern const float native_cull_screen_margin_56d7bc;

namespace {

Matrix4 multiply(const Matrix4& left, const Matrix4& right) {
    Matrix4 result{};
    for (std::size_t row = 0; row < 4; ++row) {
        for (std::size_t column = 0; column < 4; ++column) {
            result.elements[row][column] =
                left.elements[row][0] * right.elements[0][column] +
                left.elements[row][1] * right.elements[1][column] +
                left.elements[row][2] * right.elements[2][column] +
                left.elements[row][3] * right.elements[3][column];
        }
    }
    return result;
}

} // namespace

Vector3* project_culling_vertices(Vector3* output, std::uint32_t output_stride,
                                  const Vector3* input, std::uint32_t input_stride,
                                  const NativeViewport& viewport,
                                  const Matrix4& projection, const Matrix4& view,
                                  const Matrix4& world, std::uint32_t count) {
    const Matrix4 world_view = multiply(world, view);
    const Matrix4 world_view_projection = multiply(world_view, projection);
    auto* output_bytes = reinterpret_cast<std::uint8_t*>(output);
    const auto* input_bytes = reinterpret_cast<const std::uint8_t*>(input);
    const float half_width = static_cast<float>(viewport.width) * 0.5f;
    const float half_height = static_cast<float>(viewport.height) * 0.5f;
    const float depth_range = viewport.max_z - viewport.min_z;

    for (std::uint32_t index = 0; index < count; ++index) {
        Vector3 point;
        std::memcpy(&point, input_bytes + index * input_stride, sizeof(point));
        const auto& m = world_view_projection.elements;
        const float clip_x = point.x * m[0][0] + point.y * m[1][0] +
                             point.z * m[2][0] + m[3][0];
        const float clip_y = point.x * m[0][1] + point.y * m[1][1] +
                             point.z * m[2][1] + m[3][1];
        const float clip_z = point.x * m[0][2] + point.y * m[1][2] +
                             point.z * m[2][2] + m[3][2];
        const float clip_w = point.x * m[0][3] + point.y * m[1][3] +
                             point.z * m[2][3] + m[3][3];
        const float reciprocal_w = 1.0f / clip_w;
        Vector3 projected{
            static_cast<float>(viewport.x) + (1.0f + clip_x * reciprocal_w) * half_width,
            static_cast<float>(viewport.y) + (1.0f - clip_y * reciprocal_w) * half_height,
            viewport.min_z + clip_z * reciprocal_w * depth_range};
        std::memcpy(output_bytes + index * output_stride, &projected, sizeof(projected));
    }
    return output;
}

std::int32_t StageResourceObjectRecord::is_outside_viewport(
    const Vector3& instance_offset, float max_distance_squared,
    const ViewportState& viewport) const {
    // Native object parameters +0x18 and +0x24 are two consecutive Vector3
    // values: object-space center and full bounds extent.
    const Vector3 position = parameters.bounds_center;
    const Vector3 half_extent{parameters.bounds_extent.x / 2.0f,
                              parameters.bounds_extent.y / 2.0f,
                              parameters.bounds_extent.z / 2.0f};
    const Vector3 relative = position + instance_offset -
                             (viewport.vector_00 + viewport.vector_3c);
    const float distance_squared = relative.x * relative.x +
                                   relative.y * relative.y +
                                   relative.z * relative.z;
    if (!(distance_squared <= max_distance_squared))
        return 1;
    // The original gate reads the raw DWORD at object+4: any nonzero value
    // bypasses projected bounds.
    if (parameters.projected_bounds_bypass != 0)
        return 0;

    const float x = position.x;
    const float y = position.y;
    const float z = position.z;
    const float hx = half_extent.x;
    const float hy = half_extent.y;
    const float hz = half_extent.z;
    const float half_z = hz / 2.0f;
    const std::array<Vector3, 16> corners{{
        {x + hx, y + hy, z + hz},
        {x + hx, y + hy, z - hz},
        {x + hx, y - hy, z + hz},
        {x + hx, y - hy, z - hz},
        {x - hx, y + hy, z + hz},
        {x - hx, y + hy, z - hz},
        {x - hx, y - hy, z + hz},
        {x - hx, y - hy, z - hz},
        {x, y - hy, z - hz},
        {x, y + hy, z - hz},
        {x, y - hy, z + hz},
        {x, y + hy, z + hz},
        {x, y - hy, z},
        {x, y + hy, z},
        {x, y - hy, z - half_z},
        {x, y + hy, z + half_z}}};

    Matrix4 world{};
    matrix_identity(&world);
    world.elements[3][0] = instance_offset.x;
    world.elements[3][1] = instance_offset.y;
    world.elements[3][2] = instance_offset.z;
    Matrix4 projection{};
    Matrix4 view{};
    std::memcpy(&projection, &viewport.projection, sizeof(projection));
    std::memcpy(&view, &viewport.view, sizeof(view));
    std::array<Vector3, 16> projected{};
    project_culling_vertices(projected.data(), sizeof(Vector3), corners.data(),
                             sizeof(Vector3), viewport.viewport, projection, view,
                             world, static_cast<std::uint32_t>(corners.size()));

    const float left = static_cast<float>(viewport.viewport.x);
    const float top = static_cast<float>(viewport.viewport.y);
    float minimum_x = left + native_cull_screen_width_56cdac + native_cull_screen_margin_56d7bc;
    float maximum_x = left - native_cull_screen_margin_56d7bc;
    float minimum_y = top + native_cull_screen_height_56cda8 + native_cull_screen_margin_56d7bc;
    float maximum_y = top - native_cull_screen_margin_56d7bc;

    for (const Vector3& point : projected) {
        if (point.z < native_zero_56e0e8 || point.z > native_one_56c8cc)
            continue;
        if (point.x <= minimum_x && minimum_x != point.x)
            minimum_x = point.x;
        if (maximum_x < point.x)
            maximum_x = point.x;
        if (point.y <= minimum_y && minimum_y != point.y)
            minimum_y = point.y;
        if (maximum_y < point.y)
            maximum_y = point.y;
    }

    if (left + native_zero_56e0e8 <= maximum_x &&
        minimum_x <= left + native_cull_screen_width_56cdac + native_zero_56e0e8 &&
        top + native_zero_56e0e8 <= maximum_y &&
        minimum_y <= top + native_cull_screen_height_56cda8 + native_zero_56e0e8)
        return 0;
    return 1;
}

} // namespace th20
