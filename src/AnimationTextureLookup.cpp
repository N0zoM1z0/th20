// Original complete 60-byte game renderer texture lookup 0x00445A00.
// Use actual ID high-24 signed file slot and low-8 24-byte TextureRecord
// offset, with authentic 42-slot checked std::array::at native E8 method.
// Plain operator[] emits the same 60B caller body but a *different* COFF
// target symbol; the immutable original callee is the checked 34B at().
// The receiver is the shared no-new-storage AnimationQuadSubmitOwner ABI.
#include "AnimationQuadSubmitOwner.hpp"
#include "AnimationFile.hpp"
#include "GraphicsApi.hpp"
#include <array>
#include <cstdint>

namespace th20 {
#if defined(_M_IX86)
static_assert(sizeof(TextureRecord) == 0x18);
static_assert(offsetof(AnimationFile, textures) == 0x58);
#endif
IDirect3DBaseTexture9* AnimationQuadSubmitOwner::texture_for_sprite(std::uint32_t id) {
    auto& files = *reinterpret_cast<std::array<AnimationFile*, 42>*>(
        reinterpret_cast<std::uint8_t*>(this) + 0x06000730);
    return files.at(static_cast<std::int32_t>(id) >> 8)->textures[id & 0xffu].texture;
}
} // namespace th20
