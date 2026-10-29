// Entire natural gameplay implementation of the original 192-byte
// AnimationPoolOwner submission-queue flush at 0x004455C0. NONEXACT until
// a full-original-byte and relocation strict comparison passes: the current
// candidate has the original 192B/55 x86 extent but differs in D3D virtual
// dispatch evaluation order. Do not award original code byte credit.
// Keep unknown multi-megabyte owner fields as separately native-attested
// offsets instead of inventing a padded 130-MiB Renderer layout.
#include "AnimationRuntimeOwner.hpp"
#include "Graphics.hpp"
#include "SpriteVertices.hpp"
#include <cstdint>

namespace th20 {
void AnimationPoolOwner::flush_draws() {
    if (*reinterpret_cast<std::uint32_t*>(
            reinterpret_cast<std::uint8_t*>(this) + 0x6000E70) != 0) {
        graphics_api::Device* device = process_graphics.get_device();
        device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
        graphics_api::Device* draw_device = process_graphics.get_device();
        std::uint32_t primitive_count =
            *reinterpret_cast<std::uint32_t*>(
                reinterpret_cast<std::uint8_t*>(this) + 0x6000E70) * 2;
        void* stream = *reinterpret_cast<void**>(
            reinterpret_cast<std::uint8_t*>(this) + 0x7C00E78);
        draw_device->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
                                     primitive_count, stream,
                                     sizeof(SpriteTexturedVertex));
        *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(this) + 0x7C00E78) =
            *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(this) + 0x7C00E74);
        *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this) + 0x6000E70) = 0;
        ++*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this) + 0xC4);
    }
}
} // namespace th20
