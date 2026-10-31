// Original 578B native text rendering Boss — source-present, NONEXACT.
// This is the full acquired format/lock/sprite/draw protocol; five original
// SSE operand bytes and the unsigned conversion table owner are still open.
#include "NativeAsciiTextDrawView.hpp"
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
void __cdecl format_text_447940(wchar_t*,const wchar_t*,va_list);
extern const float native_text_sizes_56c768[];
extern const float native_double_56c8d0;
extern const float native_one_56c8cc;
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
    // Physical stack buffer: 0x500 bytes. The format wrapper passes a
    // 0x500 count to the wide CRT; its full bounds/encoding contract
    // remains unresolved and is NOT asserted safe for arbitrary input.
    wchar_t formatted[0x280];
    va_list args;
    va_start(args,format);
    format_text_447940(formatted,reinterpret_cast<const wchar_t*>(format),args);
    va_end(args);
    SpriteData* sprite=animation->sprite_data();
    transform.field_a=animation->base.field_3a8;
    transform.field_b=animation->base.field_3ac;
    transform.field_c=animation->base.field_3b0;
    transform.field_d=animation->base.field_3b4;
    animation->base.flags.bit_10 = 1;
    auto shadow=static_cast<std::int32_t>((animation->base.flags.word_04>>10)&1);
    // Unsigned byte count -> float follows the native two-lane correction
    // sequence. The compiler's exact XMM operand register choice differs.
    std::int32_t x=static_cast<std::int32_t>(sprite->extent_4c -
       (((glyph_width*native_double_56c8d0-native_one_56c8cc) *
       static_cast<float>(std::strlen(reinterpret_cast<const char*>(formatted))))
       / native_double_56c8d0));
    auto* texture=reinterpret_cast<AnimationQuadSubmitOwner*>(this)->texture_for_sprite(sprite->texture_id);
    return this->submit_text_44fff0(
       texture,sprite,x,layer,color,reinterpret_cast<const char*>(formatted),
       shadow,font,align<<1,&transform,mode,callback);
}
}
