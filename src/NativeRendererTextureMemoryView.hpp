#pragma once
// Shared non-owning Renderer C++ ABI for actual D3D9 upload/finalization.
// This class has no synthetic fields, allocation, alternate Renderer owner
// or source-code-level claim about the currently unrecovered full layout.
#include <cstdint>
struct IDirect3DTexture9;
namespace th20 {
struct TextureRecord;
struct NativeRendererTextureMemoryView {
    void finalize_uploaded_texture_451910(IDirect3DTexture9* texture);
    std::int32_t create_uploaded_texture_44e8f0(
        TextureRecord* record, std::int32_t native_format,
        std::int32_t original_parameter_10,
        std::int32_t width, std::int32_t height,
        std::int32_t left,std::int32_t top,
        std::int32_t clipped_width,std::int32_t clipped_height);
};
}
