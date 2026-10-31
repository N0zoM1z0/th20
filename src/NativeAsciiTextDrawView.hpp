#pragma once
#include <cstdint>
#include <functional>
struct IDirect3DBaseTexture9;
namespace th20 {
class Animation;
struct SpriteData;
// Both value words are currently opaque. Native 578B/294B callers establish
// an eight-byte returned object, not its complete semantic field names.
struct NativeTextDrawResult8 {
    std::uint32_t first, second;
};
// Original caller copies four genuine Animation+0x3A8..+0x3B4 words.
struct NativeTextTransform4 {
    std::int32_t field_a, field_b, field_c, field_d;
};
// This is a borrowed Renderer/AnimationPool ABI. The format method is a
// variadic __cdecl MEMBER, so its 'this' is passed on the stack, before
// the implicit 8B return buffer; submit is ordinary __thiscall (this ECX).
struct NativeTextSubmitOwner {
    NativeTextDrawResult8 submit_text_44fff0(
        IDirect3DBaseTexture9* texture, SpriteData* sprite,
        std::int32_t horizontal_offset, std::int32_t layer,
        std::uint32_t color, const char* formatted,
        std::int32_t bit10, std::int32_t font, std::int32_t align,
        const NativeTextTransform4* transform, std::int32_t mode,
        std::function<void()> callback);
    NativeTextDrawResult8 __cdecl draw_44b020(
        Animation* animation, std::int32_t layer, std::uint32_t color,
        std::int32_t font, std::int32_t align, std::int32_t mode,
        std::function<void()> callback, const char* format, ...);
};
#if defined(_M_IX86)
static_assert(sizeof(NativeTextDrawResult8)==8);
static_assert(sizeof(NativeTextTransform4)==16);
#endif
}
