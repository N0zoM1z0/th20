// Original Renderer formatted sprite-text call. Format under lock slot nine,
// then submit using the live animation transform and a by-value callback.
#include "NativeRendererFormattedTextView.hpp"
#include "AnimationQuadSubmitOwner.hpp"
#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "LockRegistry.hpp"
#include <cstdarg>
#include <functional>
#include <mutex>
#include <cstdint>

namespace th20 {
extern void __cdecl format_text_447940(wchar_t*, const wchar_t*, va_list);

NativeTextDrawResult8 __cdecl NativeRendererFormattedTextView::draw_formatted_text_44ac20(
    Animation* animation, std::int32_t layer, std::uint32_t color,
    std::int32_t font, std::int32_t horizontal, std::int32_t align,
    std::int32_t mode, std::function<void()> callback,
    const wchar_t* format, ...) {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(9));
    wchar_t formatted[640];
    va_list arguments;
    va_start(arguments, format);
    format_text_447940(formatted, format, arguments);
    va_end(arguments);
    SpriteData* sprite = animation->sprite_data();
    NativeTextTransform4 transform {
        animation->base.field_3a8, animation->base.field_3ac,
        animation->base.field_3b0, animation->base.field_3b4
    };
    animation->base.flags.bit_10 = 1;
    std::uint32_t bit10 = (animation->base.flags.word_04 >> 10) & 1;
    auto* texture = reinterpret_cast<AnimationQuadSubmitOwner*>(this)
        ->texture_for_sprite(sprite->texture_id);
    return submit_text_44fff0(texture, sprite, horizontal << 1, layer, color,
        reinterpret_cast<const char*>(formatted), bit10, font, align << 1,
        &transform, mode, callback);
}
}
