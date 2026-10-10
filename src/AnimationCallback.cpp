#include "AnimationCallback.hpp"
#include "Animation.hpp"
#include "Bullet.hpp"
#include "BulletStyle.hpp"
#include "DiagnosticAllocator.hpp"
namespace th20 {
AnimationCallback::AnimationCallback(Animation* receiver) : animation(nullptr) {
    animation = receiver;
    receiver->set_callback(this);
}
AnimationCallback::~AnimationCallback() = default;
std::int32_t AnimationCallback::update() { return 0; }
std::int32_t AnimationCallback::draw() { return 0; }
std::int32_t AnimationCallback::slot_0c() { return 0; }
std::int32_t AnimationCallback::interrupt(std::int32_t) { return 0; }
AnimationCallback* Animation::set_callback(AnimationCallback* value) {
    callback = value;
    return value;
}
void Animation::interrupt(std::int32_t event) {
    if (callback) callback->interrupt(event);
    base.field_438 = event;
}
std::int32_t Bullet::type() const { return field_4c; }
std::int32_t Bullet::color_index() const { return field_4e; }
std::int32_t bullet_animation_script(Animation* animation, std::int32_t script) {
    Bullet* bullet = static_cast<Bullet*>(animation->user_data);
    if (static_cast<std::int32_t>(bullet_styles[bullet->type()].colors[0].words[0]) >= 0)
        return static_cast<std::int32_t>(bullet_styles[bullet->type()].colors[bullet->color_index()].words[script]);
    else
        return script;
}
template void DiagnosticAllocator::release_object<AnimationCallback>(AnimationCallback*);
}
