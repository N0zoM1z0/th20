// CORE/RECON-1173: the original unsigned-length correction data at 0x56CDD0
// is now a typed const double[2] owner. The natural-C++ candidate keeps the
// exact native call/data roles; current MSVC fuses one scalar load/multiply.
// Original 578B native text rendering Boss — source-present, NONEXACT.
// Current natural-C++ candidate is 574B/138 i386; it now names the original
// unsigned conversion table directly. No ASM, padding, or target patching.
#include "NativeAsciiTextDrawView.hpp"
#include "AnimationTextFormat.hpp"
#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "AnimationQuadSubmitOwner.hpp"
#include "LockRegistry.hpp"
#include <cstdarg>
#include <cstring>
#include <cstdint>
#include <functional>
#include <mutex>
namespace th20 {
extern const float native_text_sizes_56c768[];
extern const float native_double_56c8d0;
extern const float native_one_56c8cc;
extern const double native_unsigned_length_correction_56cdd0[2];
NativeTextDrawResult8 __cdecl NativeTextSubmitOwner::draw_44b020(
 Animation* animation,
 std::int32_t layer,std::uint32_t color,std::int32_t font,
 std::int32_t align,std::int32_t mode,std::function<void()> callback,
 const char* format, ...)
{
    // The native stack reserves the four-word transform before the guard.
    NativeTextTransform4 transform;
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(9));
    float glyph_width=native_text_sizes_56c768[font];
    char formatted[0x500];
    va_list args;
    va_start(args,format);
    format_text_447940(formatted,format,args);
    va_end(args);
    SpriteData* sprite=animation->sprite_data();
    transform.field_a=animation->base.field_3a8;
    transform.field_b=animation->base.field_3ac;
    transform.field_c=animation->base.field_3b0;
    transform.field_d=animation->base.field_3b4;
    animation->base.flags.bits_02.bit_10 = 1;
    auto shadow=static_cast<std::int32_t>((animation->base.flags.word_04>>10)&1);
    // The signed cvtsi2sd plus sign-selected native correction table preserves
    // the original unsigned byte-count conversion for the full uint32 range.
    const float width_factor =
        glyph_width*native_double_56c8d0-native_one_56c8cc;
    const std::uint32_t byte_length = static_cast<std::uint32_t>(
        std::strlen(formatted));
    const double corrected_length =
        static_cast<double>(static_cast<std::int32_t>(byte_length)) +
        native_unsigned_length_correction_56cdd0[byte_length >> 31];
    std::int32_t x=static_cast<std::int32_t>(
        sprite->extent_4c -
        (width_factor*static_cast<float>(corrected_length))/native_double_56c8d0);
    auto* texture=reinterpret_cast<AnimationQuadSubmitOwner*>(this)->texture_for_sprite(sprite->texture_id);
    return this->submit_text_44fff0(
       texture,sprite,x,layer,color,formatted,
       shadow,font,align<<1,&transform,mode,callback);
}
}
