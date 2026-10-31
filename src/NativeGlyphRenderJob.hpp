#pragma once
#include "NativeGlyphCanvasStorage.hpp"
#include "NativeAsciiTextDrawView.hpp"
#include <d3d9.h>
#include <cstddef>
#include <cstdint>
#include <functional>
namespace th20 {
// Canonical, genuine 0x58-byte queued glyph render closure, shared by the
// whole-exact 132B capture, 23B destructor and 360B D3D9 upload operator.
// The +0x04 word is a D3D texture COM pointer, NOT the earlier color guess;
// +0x28 is a pointer to the completion byte, NOT an integer render mode.
// +0x2C is real storage but is not written by the original constructor.
struct NativeGlyphRenderJob {
    NativeGlyphCanvasStorage* canvas;
    IDirect3DBaseTexture9* target_texture;
    NativeTextTransform4 geometry;
    NativeTextTransform4 texture_region;
    std::uint8_t* completion_flag;
    std::uint32_t unresolved_2c;
    std::function<void()> callback;
    NativeGlyphRenderJob(NativeGlyphCanvasStorage* source,
                         IDirect3DBaseTexture9* const& texture_value,
                         const NativeTextTransform4& geometry_value,
                         const NativeTextTransform4& texture_value_region,
                         std::uint8_t* const& completion_value,
                         const std::function<void()>& task)
        : canvas(source),target_texture(texture_value),geometry(geometry_value),
          texture_region(texture_value_region),completion_flag(completion_value),
          callback(task) {}
    void operator()() const;
};
#if defined(_M_IX86)
static_assert(sizeof(NativeGlyphRenderJob)==0x58);
static_assert(offsetof(NativeGlyphRenderJob,target_texture)==0x04);
static_assert(offsetof(NativeGlyphRenderJob,geometry)==0x08);
static_assert(offsetof(NativeGlyphRenderJob,texture_region)==0x18);
static_assert(offsetof(NativeGlyphRenderJob,completion_flag)==0x28);
static_assert(offsetof(NativeGlyphRenderJob,callback)==0x30);
#endif
}
