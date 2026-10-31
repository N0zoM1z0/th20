// Entire original 155B game-owned dynamic D3D9 texture creator.
// The native method-pointer lookup precedes the format-value assignment:
// the true format local is assigned during the CreateTexture argument.
// This preserves original COM call evaluation and all seven physical roles.
#include "NativeRendererTextureCreate.hpp"
#include "AnimationFile.hpp"
#include "Graphics.hpp"
#include "EclDiagnostic.hpp"
#include <d3d9.h>
#include <cstdint>
namespace th20 {
// Original native table at 0x0056E22C; its physical data placement and
// ownership remain separate from this function's source/ABI reconstruction.
extern const std::uint32_t texture_byte_sizes[9];
const std::uint32_t texture_byte_sizes[9] = {4,4,4,4,4,4,4,4,4};

std::int32_t NativeRendererTextureOwner::create_dynamic_texture_44c0b0(
    TextureRecord* record, std::int32_t width, std::int32_t height,
    std::int32_t format) {
    record->flags.bits = (record->flags.bits & ~3u) | 2u;
    auto* device = process_graphics.get_device();
    graphics_api::TextureFormat selected_format;
    if (device->CreateTexture(width, height, 1, D3DUSAGE_DYNAMIC,
                              (selected_format = texture_api_formats[format]),
                              D3DPOOL_DEFAULT,
                              &record->texture, nullptr) != 0) {
        ecl_diagnostic_hint("error D3DXCreateTexture\n");
    }
    record->bytes_per_pixel = texture_byte_sizes[format];
    return width * height * texture_byte_sizes[format];
}
}
