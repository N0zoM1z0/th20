// Complete original centered Unicode Renderer text path; current natural
// C++20 source remains NONEXACT in the SSE width/offset expression.
#include "NativeRendererFormattedTextView.hpp"
#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "AnimationQuadSubmitOwner.hpp"
#include "LockRegistry.hpp"
#include <cstdarg>
#include <cstring>
#include <cstdint>
#include <functional>
#include <mutex>

namespace th20 {
extern void __cdecl format_text_447940(wchar_t*, const wchar_t*, va_list);
extern const float native_text_sizes_56c768[];
extern const float native_double_56c8d0;
extern const float native_one_56c8cc;

NativeTextDrawResult8 __cdecl NativeRendererFormattedTextView::draw_centered_text_44add0(
    Animation* animation, std::int32_t layer, std::uint32_t color,
    std::int32_t font, std::int32_t align, std::int32_t mode,
    std::function<void()> callback, const wchar_t* format, ...) {
    NativeTextTransform4 transform;
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(9));
    float glyph_width = native_text_sizes_56c768[font];
    wchar_t formatted[640];
    va_list arguments;
    va_start(arguments, format);
    format_text_447940(formatted, format, arguments);
    va_end(arguments);
    SpriteData* sprite = animation->sprite_data();
    transform.field_a = animation->base.field_3a8;
    transform.field_b = animation->base.field_3ac;
    transform.field_c = animation->base.field_3b0;
    transform.field_d = animation->base.field_3b4;
    animation->base.flags.bit_10 = 1;
    std::uint32_t bit10 = (animation->base.flags.word_04 >> 10) & 1;
    std::int32_t offset = static_cast<std::int32_t>(
        sprite->extent_4c / native_double_56c8d0 -
        ((static_cast<float>(std::strlen(reinterpret_cast<const char*>(formatted))) *
          (glyph_width * native_double_56c8d0 - native_one_56c8cc)) / 4.0f));
    auto* texture = reinterpret_cast<AnimationQuadSubmitOwner*>(this)
        ->texture_for_sprite(sprite->texture_id);
    return submit_text_44fff0(texture, sprite, offset, layer, color,
        reinterpret_cast<const char*>(formatted), bit10, font, align << 1,
        &transform, mode, callback);
}
}
