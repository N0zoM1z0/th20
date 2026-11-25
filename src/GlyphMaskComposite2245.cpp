// Game-owned 2,245B glyph compositor at 0x00416420. SOURCE-PRESENT,
// NONEXACT: both native pixel-format branches and the 16B PMR-vector
// offsets are reconstructed. The PMR insertion/growth/backout chain now
// restores the 108B/140B/488B/200B bodies and the nested 92B/31B helper
// shapes outside real relocation fields. The 35B wrapper is 34B with the
// original compiler-emitted trailing NOP absent; the complete game
// compositor remains NONEXACT (current full parent: 2,177B/581 i386).
#include "NativeGlyphCanvasView.hpp"
#include "NativeGlyphMaskOffsets.hpp"
#include "DiagnosticAllocator.hpp"
#include "EffectParameters.hpp"
#include <cstdint>
#include <cstring>
#include <memory_resource>
#include <vector>
#include <utility>

// TH20's glyph-offset vector was emitted by an older MSVC STL. The pinned
// newer STL folds the old pointer-forwarding calls and changes the growth
// stack/exception layout, so preserve the original member-template call graph
// with explicit specializations for this user-defined std::array element type.
// These are ordinary C++ implementations, not injected bytes or padding; the
// 35B public wrapper remains NONEXACT because this compiler omits its NOP.
// The main Boss uses a two-case pixel-format dispatch, constructs each PMR
// stencil only after computing radius_squared, and takes the BGRA outline
// edge directly from each of the four ordered neighbor tests.
template __declspec(noinline) const th20::GlyphMaskOffset&&
std::move<const th20::GlyphMaskOffset&>(const th20::GlyphMaskOffset&) noexcept;
template __declspec(noinline) th20::GlyphMaskOffset&&
std::move<th20::GlyphMaskOffset&>(th20::GlyphMaskOffset&) noexcept;
// The original 200B uninitialized-move loop forwards its raw current
// iterator through the same out-of-line pointer-lvalue move helper.
template __declspec(noinline) th20::GlyphMaskOffset*&&
std::move<th20::GlyphMaskOffset*&>(th20::GlyphMaskOffset*&) noexcept;

namespace th20 {
using GlyphMaskAllocator = std::pmr::polymorphic_allocator<GlyphMaskOffset>;
__declspec(noinline) void glyph_uninitialized_move_construct(
    GlyphMaskAllocator& allocator, GlyphMaskOffset& destination, const GlyphMaskOffset& source) {
    allocator.construct(&destination, std::move(source));
}
} // namespace th20

namespace std {
template <>
class _Uninitialized_backout_al<th20::GlyphMaskAllocator> {
    using _Alloc = th20::GlyphMaskAllocator;
    using pointer = th20::GlyphMaskOffset*;
public:
    __declspec(noinline) _Uninitialized_backout_al(pointer destination, _Alloc& allocator)
        : _First(destination), _Last(destination), _Al(allocator) {}
    _Uninitialized_backout_al(const _Uninitialized_backout_al&) = delete;
    _Uninitialized_backout_al& operator=(const _Uninitialized_backout_al&) = delete;
    __declspec(noinline) ~_Uninitialized_backout_al() {
        _STD _Destroy_range(_First, _Last, _Al);
    }
    template <class... _Types>
    __declspec(noinline) void _Emplace_back(_Types&&... values) {
        _Normal_allocator_traits<_Alloc>::construct(_Al, _STD _Unfancy(_Last), _STD forward<_Types>(values)...);
        ++_Last;
    }
    __declspec(noinline) void _Emplace_back_deref_move(th20::GlyphMaskOffset&& source) {
        th20::GlyphMaskOffset&& moved_source = _STD move(source);
        th20::GlyphMaskOffset&& moved_destination = _STD move(*_Last);
        _Alloc& allocator = _Al;
        th20::glyph_uninitialized_move_construct(allocator, moved_destination, moved_source);
        _Last += 1;
    }
    constexpr __declspec(noinline) pointer _Release() {
        _First = _Last;
        return _Last;
    }
private:
    pointer _First;
    pointer _Last;
    _Alloc& _Al;
};

// Keep the older backout's const-reference allocator-traits path available:
// this is a genuine native 22B child and is independent of the newer
// polymorphic_allocator::construct wrapper used by the move-backout bridge.
template __declspec(noinline) void
_Uninitialized_backout_al<th20::GlyphMaskAllocator>::_Emplace_back<const th20::GlyphMaskOffset&>(
    const th20::GlyphMaskOffset&);

template <>
_CONSTEXPR20 __declspec(noinline) _Alloc_ptr_t<th20::GlyphMaskAllocator>
_Uninitialized_move<th20::GlyphMaskOffset*, th20::GlyphMaskAllocator>(
    th20::GlyphMaskOffset* first, th20::GlyphMaskOffset* last,
    _Alloc_ptr_t<th20::GlyphMaskAllocator> destination, th20::GlyphMaskAllocator& allocator) {
    auto unwrapped_first = _STD _Get_unwrapped(first);
    const auto unwrapped_last = _STD _Get_unwrapped(last);
    _Uninitialized_backout_al<th20::GlyphMaskAllocator> backout{destination, allocator};
    for (; unwrapped_first != unwrapped_last; ++unwrapped_first) {
        backout._Emplace_back_deref_move(_STD move(*unwrapped_first));
    }
    return backout._Release();
}
} // namespace std

namespace std {
template <>
template <>
__declspec(noinline) th20::GlyphMaskOffset&
vector<th20::GlyphMaskOffset, pmr::polymorphic_allocator<th20::GlyphMaskOffset>>::_Emplace_back_with_unused_capacity<const th20::GlyphMaskOffset&>(
    const th20::GlyphMaskOffset& value) {
    auto& data = _Mypair._Myval2;
    pointer& last = data._Mylast;
    th20::glyph_uninitialized_move_construct(_Getal(), *_Unfancy(last), std::move(value));
    _Orphan_range(last, last);
    th20::GlyphMaskOffset& result = *last;
    ++last;
    return result;
}

template <>
template <>
__declspec(noinline) vector<th20::GlyphMaskOffset, pmr::polymorphic_allocator<th20::GlyphMaskOffset>>::pointer
vector<th20::GlyphMaskOffset, pmr::polymorphic_allocator<th20::GlyphMaskOffset>>::_Emplace_reallocate<const th20::GlyphMaskOffset&>(
    const pointer where, const th20::GlyphMaskOffset& value) {
    _Alty& allocator = _Getal();
    auto& data = _Mypair._Myval2;
    pointer& first = data._Myfirst;
    pointer& last = data._Mylast;

    const size_type where_offset = static_cast<size_type>(where - first);
    const size_type old_size = static_cast<size_type>(last - first);
    if (old_size == max_size()) {
        _Xlength();
    }

    const size_type new_size = old_size + 1;
    size_type new_capacity = _Calculate_growth(new_size);
    const pointer new_vector = _STD _Allocate_at_least_helper(allocator, new_capacity);
    const pointer constructed_last = new_vector + where_offset + 1;
    _Reallocation_guard guard{allocator, new_vector, new_capacity, constructed_last, constructed_last};
    auto& constructed_first = guard._Constructed_first;

    const th20::GlyphMaskOffset&& source = std::move(value);
    const pointer destination = _Unfancy(new_vector + where_offset);
    th20::glyph_uninitialized_move_construct(allocator, *destination, source);
    constructed_first = new_vector + where_offset;

    if (where == last) {
        if constexpr (is_nothrow_move_constructible_v<value_type> || !is_copy_constructible_v<value_type>) {
            _STD _Uninitialized_move(first, last, new_vector, allocator);
        } else {
            _STD _Uninitialized_copy(first, last, new_vector, allocator);
        }
    } else {
        _STD _Uninitialized_move(first, where, new_vector, allocator);
        constructed_first = new_vector;
        _STD _Uninitialized_move(where, last, new_vector + where_offset + 1, allocator);
    }

    guard._New_begin = nullptr;
    _Change_array(new_vector, new_size, new_capacity);
    return new_vector + where_offset;
}

template <>
template <>
__declspec(noinline) th20::GlyphMaskOffset&
vector<th20::GlyphMaskOffset, pmr::polymorphic_allocator<th20::GlyphMaskOffset>>::_Emplace_one_at_back<const th20::GlyphMaskOffset&>(
    const th20::GlyphMaskOffset& value) {
    auto& data = _Mypair._Myval2;
    pointer& last = data._Mylast;
    if (last != data._Myend) {
        return _Emplace_back_with_unused_capacity<const th20::GlyphMaskOffset&>(std::move(value));
    }
    return *_Emplace_reallocate<const th20::GlyphMaskOffset&>(last, std::move(value));
}

template <>
template <>
__declspec(noinline) th20::GlyphMaskOffset&
vector<th20::GlyphMaskOffset, pmr::polymorphic_allocator<th20::GlyphMaskOffset>>::emplace_back<const th20::GlyphMaskOffset&>(
    const th20::GlyphMaskOffset& value) {
    return _Emplace_one_at_back<const th20::GlyphMaskOffset&>(std::move(value));
}
} // namespace std
namespace th20 {
struct NativeGlyphAlpha4444 {
    std::uint16_t blue : 4;
    std::uint16_t green : 4;
    std::uint16_t red : 4;
    std::uint16_t alpha : 4;
};
static_assert(sizeof(NativeGlyphAlpha4444)==2);

// Native original 16-bit color word is default-constructed before
// alpha/RGB nibbles are subsequently assigned on the true ARGB4444 path.
struct NativeGlyphColor4444 {
    std::uint16_t packed;
    NativeGlyphColor4444() : packed(0) {}
};
bool NativeGlyphCanvasView::composite_glyph_mask_416420(
    std::int32_t rows,std::int32_t start,std::int32_t end,
    std::uint32_t color,float radius) {
    // Snapshot the original DIB extent before changing any live pixel data.
    const std::int32_t length=pixel_stride_4156c0()*rows;
    auto* pixels=bitmap_pixels_4156a0();
    auto* original=process_allocator->allocate_array<std::uint8_t>(
        "D:\\cygwin\\home\\zun\\prog\\th20\\src\\core\\grpfont.cpp:615 u_char",length);
    std::memcpy(original,pixels,length);
    switch (*reinterpret_cast<const std::int32_t*>(
        reinterpret_cast<const std::uint8_t*>(this)+0x100)) {
    case 0x15: {
        const float radius_squared=radius*radius;
        GlyphMaskOffsets offsets;
        for (std::int32_t delta_y=0;delta_y<static_cast<std::int32_t>(radius_squared);++delta_y) {
            for (std::int32_t delta_x=0;delta_x<static_cast<std::int32_t>(radius_squared);++delta_x) {
                if (static_cast<float>(delta_x*delta_x+delta_y*delta_y)<radius_squared &&
                    (delta_y!=0 || delta_x!=0)) {
                    const GlyphMaskOffset displacement{delta_x,delta_y};
                    offsets.emplace_back(displacement);
                }
            }
        }
        // One immutable stencil base serves every row and neighbor test.
        const auto* stencil=reinterpret_cast<const PackedColorChannels*>(original);
        PackedColor opaque(color);
        const std::int32_t row_words=pixel_stride_4156c0()/4;
        // The native outline color flips only the packed alpha byte in place.
        opaque.channels.alpha = static_cast<std::uint8_t>(opaque.channels.alpha ^ 0xffu);
        std::int32_t row_advance=0;
        // Native update edge reads the live stride before the row test.
        for (std::int32_t y=0;y<rows;
             ++y,row_advance+=pixel_stride_4156c0()) {
            auto* dest=reinterpret_cast<std::uint32_t*>(
                pixels+row_advance+start*4);
            for (std::int32_t x=start;x<end;++x,++dest) {
                if (reinterpret_cast<const PackedColorChannels*>(dest)->alpha!=0) {
                    for (const GlyphMaskOffset& off:offsets) {
                    // The original has two genuine E8 calls per vector
                    // element to the folded 22B array-index helper.
                    const std::int32_t delta_x=off[0];
                    const std::int32_t delta_y=off[1];
                        if (x-delta_x>=0 && y-delta_y>=0 &&
                            stencil[(y-delta_y)*row_words+x-delta_x].alpha!=0xff) {
                            goto bgra32_outline;
                        }
                        if (x+delta_x<canvas_width_415800() && y-delta_y>=0 &&
                            stencil[(y-delta_y)*row_words+x+delta_x].alpha!=0xff) {
                            goto bgra32_outline;
                        }
                        if (x-delta_x>=0 && y+delta_y<rows &&
                            stencil[(y+delta_y)*row_words+x-delta_x].alpha!=0xff) {
                            goto bgra32_outline;
                        }
                        if (x+delta_x<canvas_width_415800() && y+delta_y<rows &&
                            stencil[(y+delta_y)*row_words+x+delta_x].alpha!=0xff) {
                            goto bgra32_outline;
                        }
                    }
                    reinterpret_cast<std::uint8_t*>(dest)[0]=opaque.channels.blue;
                    reinterpret_cast<std::uint8_t*>(dest)[1]=opaque.channels.green;
                    reinterpret_cast<std::uint8_t*>(dest)[2]=opaque.channels.red;
                    goto bgra32_pixel_done;
                    bgra32_outline:
                    *reinterpret_cast<PackedColorChannels*>(dest)=opaque.channels;
                }
                bgra32_pixel_done:
                ;
            }
        }
    } break;
    case 0x1a: {
        const float radius_squared=radius*radius;
        GlyphMaskOffsets offsets;
        for (std::int32_t delta_y=0;delta_y<static_cast<std::int32_t>(radius_squared);++delta_y) {
            for (std::int32_t delta_x=0;delta_x<static_cast<std::int32_t>(radius_squared);++delta_x) {
                if (static_cast<float>(delta_x*delta_x+delta_y*delta_y)<radius_squared &&
                    (delta_y!=0 || delta_x!=0)) {
                    const GlyphMaskOffset displacement{delta_x,delta_y};
                    offsets.emplace_back(displacement);
                }
            }
        }
        const PackedColor unpacked(color);
        NativeGlyphColor4444 packed_color;
        packed_color.packed=static_cast<std::uint16_t>(
              ((unpacked.value>>4)&0xf)
             |(((unpacked.value>>12)&0xf)<<4)
             |(((unpacked.value>>20)&0xf)<<8)
             |((((unpacked.value>>28)&0xf)^0xf)<<12));
        for (std::int32_t y=0;y<rows;++y) {
            auto* dest=reinterpret_cast<std::uint16_t*>(
                pixels+y*pixel_stride_4156c0()+start*2);
            for (std::int32_t x=start;x<end;++x,++dest) {
                // Native RGBA4444 reads the *live* per-pixel source row
                // stride here, before enumerating stencil offsets. This
                // mutable scratch address then holds each real guarded
                // neighbor's source address for its alpha-nibble test.
                // Multiplication precedes signed division, as in the PE.
                const std::uint16_t* stencil=&reinterpret_cast<const std::uint16_t*>(original)[((y*pixel_stride_4156c0())/2)+x];
                for (const GlyphMaskOffset& off:offsets) {
                    // The original has two genuine E8 calls per vector
                    // element to the folded 22B array-index helper.
                    const std::int32_t delta_x=off[0];
                    const std::int32_t delta_y=off[1];
                    if (((x-delta_x>=0 && y-delta_y>=0) &&
                         ((stencil=&reinterpret_cast<const std::uint16_t*>(original)[((y-delta_y)*pixel_stride_4156c0()/2)+(x-delta_x)]), (reinterpret_cast<const NativeGlyphAlpha4444*>(stencil)->alpha!=0xf))) ||
                        ((x+delta_x<canvas_width_415800() && y-delta_y>=0) &&
                         ((stencil=&reinterpret_cast<const std::uint16_t*>(original)[((y-delta_y)*pixel_stride_4156c0()/2)+(x+delta_x)]), (reinterpret_cast<const NativeGlyphAlpha4444*>(stencil)->alpha!=0xf))) ||
                        ((x-delta_x>=0 && y+delta_y<rows) &&
                         ((stencil=&reinterpret_cast<const std::uint16_t*>(original)[((y+delta_y)*pixel_stride_4156c0()/2)+(x-delta_x)]), (reinterpret_cast<const NativeGlyphAlpha4444*>(stencil)->alpha!=0xf))) ||
                        ((x+delta_x<canvas_width_415800() && y+delta_y<rows) &&
                         ((stencil=&reinterpret_cast<const std::uint16_t*>(original)[((y+delta_y)*pixel_stride_4156c0()/2)+(x+delta_x)]), (reinterpret_cast<const NativeGlyphAlpha4444*>(stencil)->alpha!=0xf)))) {
                        *dest=packed_color.packed;
                        goto rgba4444_pixel_done;
                    }
                }
                // The native non-outline path updates the packed RGB nibbles
                // separately, preserving the destination alpha nibble. Keep
                // the original red/green/blue assignment order.
                reinterpret_cast<NativeGlyphAlpha4444*>(dest)->red =
                    reinterpret_cast<const NativeGlyphAlpha4444*>(&packed_color.packed)->red;
                reinterpret_cast<NativeGlyphAlpha4444*>(dest)->green =
                    reinterpret_cast<const NativeGlyphAlpha4444*>(&packed_color.packed)->green;
                reinterpret_cast<NativeGlyphAlpha4444*>(dest)->blue =
                    reinterpret_cast<const NativeGlyphAlpha4444*>(&packed_color.packed)->blue;
                rgba4444_pixel_done:
                ;
            }
        }
    } break;
    default:
        break;
    }
    process_allocator->release_array(original);
    return true;
}
} // namespace th20
