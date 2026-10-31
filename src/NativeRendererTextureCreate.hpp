#pragma once
#include <cstdint>
namespace th20 {
struct TextureRecord;
// Non-owning native receiver: the actual Renderer class layout and ownership
// remain unresolved. The original two methods take ECX/this and stack args.
struct NativeRendererTextureOwner {
    std::int32_t create_dynamic_texture_44c0b0(
        TextureRecord* record, std::int32_t width, std::int32_t height, std::int32_t format);
    std::int32_t create_render_target_44c150(
        TextureRecord* record, std::int32_t width, std::int32_t height);
};
}
