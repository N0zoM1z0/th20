#include "Animation.hpp"
#include "AnimationFile.hpp"
#include <cstring>
#include <type_traits>
static_assert(std::is_trivially_copyable_v<th20::AnimationBase>);
namespace th20 {
Animation* Animation::find_child(std::int32_t identifier, std::int32_t ordinal) {
    IntrusiveLink<Animation>* link = &child_links[1];
    while (link) {
        Animation* animation = link->node_value();
        if (animation && animation != this) {
            if (static_cast<std::int16_t>(animation->base.field_440) == identifier || identifier == -1) {
                if (ordinal == 0) return animation;
                --ordinal;
            }
            if (animation->child_links[1].next_value()) {
                Animation* found = animation->find_child(identifier, ordinal);
                if (found) return found;
            }
            if (static_cast<std::int16_t>(base.field_440) == -2 && !link->next_value())
                return link->node_value();
        }
        link = link->next_value();
    }
    return nullptr;
}
}

namespace th20 {
void Animation::copy_base(const Animation* source) {
    std::memcpy(&base, &source->base, sizeof(base));
}
void Animation::clear_field_570() { field_570 = 0; }
void Animation::set_field_5dc(AnimationEntryCallback value) { field_5dc = value; }
void Animation::set_field_5e0(AnimationScriptCallback value) { field_5e0 = value; }
void Animation::clear_pending_fields() {
    set_field_5dc(0);
    set_field_5e0(0);
}
void AnimationFile::apply_template(Animation* animation, std::int32_t script) {
    animation->clear_field_570();
    animation->clear_pending_fields();
    animation->copy_base(&templates[script]);
    animation->timer_4d8 = 0;
    animation->timer_4c8 = 0;
}
}
