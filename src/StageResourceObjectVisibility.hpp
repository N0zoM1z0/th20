#pragma once

#include "Matrix4.hpp"
#include "Vector3.hpp"
#include "Viewport.hpp"

#include <cstdint>

namespace th20 {

// Shared mathematical equivalent of D3DXVec3ProjectArray for the original
// Animation culler. Strides are byte counts, matching the D3DX ABI.
Vector3* project_culling_vertices(Vector3* output, std::uint32_t output_stride,
                                  const Vector3* input, std::uint32_t input_stride,
                                  const NativeViewport& viewport,
                                  const Matrix4& projection, const Matrix4& view,
                                  const Matrix4& world, std::uint32_t count);

} // namespace th20
