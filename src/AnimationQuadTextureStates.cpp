// Complete original 2,725-byte /699-instruction native game texture-state
// boss at 0x00445BC0, reproduced with 50 real E8 call roles and 57 genuine
// original PE HIGHLOW fields. Canonical comparison MUST include the complete
// 2,768-byte COFF contribution: executable body, 3-byte alignment and ten
// original 32-bit after-RET mode table pointers. The parent 3,159-byte quad
// submit is also WHOLE STRICT EXACT; only the separate 5,993-byte
// Animation Draw dispatcher remains NONEXACT. Keep independent coverage.
#include "AnimationQuadSubmitOwner.hpp"
#include "Animation.hpp"
#include "Graphics.hpp"
#include "GraphicsApi.hpp"
#include <cstdint>

namespace th20 {
// Original native 8-bit source lanes: the real 2-bit C++ bitfield protocols
// are kept local rather than editing shared Animation.hpp and triggering
// unrelated protected compiler inputs. These overlays describe *reads*
// of actual packed AnimationFlags bytes, not new persistent owner storage.
struct NativeRenderByteA2 { std::uint8_t mode:2; std::uint8_t upper:6; };
struct NativeRenderByteA1 { std::uint8_t low5:5; std::uint8_t mode:2; std::uint8_t top:1; };
static_assert(sizeof(NativeRenderByteA1)==1 && sizeof(NativeRenderByteA2)==1);
#define NATIVE_DRAW_CACHE(byte_offset) (*reinterpret_cast<std::uint8_t*>( \
    reinterpret_cast<std::uint8_t*>(this) + (byte_offset)))
#define ANIM_RAW_BYTE(byte_offset) (reinterpret_cast<const std::uint8_t*>(animation)[byte_offset])
#define D3D_SET_RENDER(state, value) (process_graphics.get_device()->SetRenderState( \
    static_cast<D3DRENDERSTATETYPE>(state), value))
#define D3D_SET_SAMPLER(state, value) (process_graphics.get_device()->SetSamplerState( \
    0, static_cast<D3DSAMPLERSTATETYPE>(state), value))

void AnimationQuadSubmitOwner::bind_native_texture_state(Animation* animation) {
    // Real original owner offsets +6000E0C/+6000E12/13/14 are byte-sized
    // state caches; source macros re-evaluate actual pointer expressions.
    if (NATIVE_DRAW_CACHE(0x6000E0C) != animation->base.flags.bytes_00.field_01) {
        flush_draws();
        NATIVE_DRAW_CACHE(0x6000E0C) = animation->base.flags.bytes_00.field_01;
        D3D_SET_RENDER(0x0F, 1);
        D3D_SET_RENDER(0xCE, 1);
        D3D_SET_RENDER(0xCF, 2);
        D3D_SET_RENDER(0xD0, 1);
        D3D_SET_RENDER(0xD1, 1);
        switch (NATIVE_DRAW_CACHE(0x6000E0C)) {
        case 0:
        default:
            D3D_SET_RENDER(0x13, 5);
            D3D_SET_RENDER(0x14, 6);
            D3D_SET_RENDER(0xAB, 1);
            break;
        case 1:
            D3D_SET_RENDER(0x13, 5);
            D3D_SET_RENDER(0x14, 2);
            D3D_SET_RENDER(0xAB, 1);
            break;
        case 2:
            D3D_SET_RENDER(0x13, 5);
            D3D_SET_RENDER(0x14, 2);
            D3D_SET_RENDER(0xAB, 3);
            break;
        case 3:
            D3D_SET_RENDER(0xF, 0);
            D3D_SET_RENDER(0x13, 2);
            D3D_SET_RENDER(0x14, 1);
            D3D_SET_RENDER(0xAB, 1);
            break;
        case 4:
            D3D_SET_RENDER(0x13, 10);
            D3D_SET_RENDER(0x14, 4);
            D3D_SET_RENDER(0xAB, 1);
            break;
        // The real native case 6 body precedes case 5 in .text. Preserve
        // this non-numerical source ordering to retain all four original
        // DWORD immediate bytes and the genuine 10-pointer jump targets.
        case 6:
            D3D_SET_RENDER(0x13, 4);
            D3D_SET_RENDER(0x14, 6);
            D3D_SET_RENDER(0xAB, 1);
            break;
        case 5:
            D3D_SET_RENDER(0x13, 9);
            D3D_SET_RENDER(0x14, 1);
            D3D_SET_RENDER(0xAB, 1);
            break;
        case 7:
            D3D_SET_RENDER(0x13, 7);
            D3D_SET_RENDER(0x14, 8);
            D3D_SET_RENDER(0xAB, 1);
            break;
        case 8:
            D3D_SET_RENDER(0x13, 5);
            D3D_SET_RENDER(0x14, 2);
            D3D_SET_RENDER(0xAB, 4);
            break;
        case 9:
            D3D_SET_RENDER(0x13, 5);
            D3D_SET_RENDER(0x14, 2);
            D3D_SET_RENDER(0xAB, 5);
            break;
        }
    }
    // Real sampler MAG/MIN (5/6) state cache uses Animation+0x4A0 bits2-3.
    if (NATIVE_DRAW_CACHE(0x6000E12) != animation->base.flags.bits_08.other_2_3) {
        flush_draws();
        NATIVE_DRAW_CACHE(0x6000E12) = animation->base.flags.bits_08.other_2_3;
        if (NATIVE_DRAW_CACHE(0x6000E12) == 0) {
            D3D_SET_SAMPLER(5, 2);
            D3D_SET_SAMPLER(6, 2);
        } else {
            D3D_SET_SAMPLER(5, 1);
            D3D_SET_SAMPLER(6, 1);
        }
    }
    // Original +0x4A2 bit 0..1 sampler state 1.
    if (NATIVE_DRAW_CACHE(0x6000E13) != (reinterpret_cast<const NativeRenderByteA2&>(animation->base.flags.field_0a).mode)) {
        flush_draws();
        NATIVE_DRAW_CACHE(0x6000E13) = (reinterpret_cast<const NativeRenderByteA2&>(animation->base.flags.field_0a).mode);
        switch (NATIVE_DRAW_CACHE(0x6000E13)) {
        case 0:
            D3D_SET_SAMPLER(1, 1);
            break;
        case 1:
            D3D_SET_SAMPLER(1, 3);
            break;
        case 2:
            D3D_SET_SAMPLER(1, 2);
            break;
        default: break;
        }
    }
    // Original +0x4A1 bits 5..6 sampler state 2.
    if (NATIVE_DRAW_CACHE(0x6000E14) != (reinterpret_cast<const NativeRenderByteA1*>(reinterpret_cast<const std::uint8_t*>(&animation->base.flags.byte_08) + 1)->mode)) {
        flush_draws();
        NATIVE_DRAW_CACHE(0x6000E14) = (reinterpret_cast<const NativeRenderByteA1*>(reinterpret_cast<const std::uint8_t*>(&animation->base.flags.byte_08) + 1)->mode);
        switch (NATIVE_DRAW_CACHE(0x6000E14)) {
        case 0:
            D3D_SET_SAMPLER(2, 1);
            break;
        case 1:
            D3D_SET_SAMPLER(2, 3);
            break;
        case 2:
            D3D_SET_SAMPLER(2, 2);
            break;
        default: break;
        }
    }
    ++*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this) + 0xC0);
}
#undef NATIVE_DRAW_CACHE
#undef ANIM_RAW_BYTE
#undef D3D_SET_RENDER
#undef D3D_SET_SAMPLER
} // namespace th20
