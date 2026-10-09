#include "ItemResourceOwners.hpp"
#include "Context.hpp"
#include "PlayerRecord.hpp"
#include "Animation.hpp"

namespace th20 {
EffectAnimationHandle::EffectAnimationHandle() noexcept {}
void StoneMenuInfo::enable() {TaskInfo::enable();}
StoneMenuInfo* stone_menu_info() {return process_stone_menu;}
AnimationFile* StoneMenuInfo::animation_file() {return file;}
EffectInfo* Context::effect_info() {return object_20;}
AnimationFile* EffectInfo::animation_file(std::int32_t index) {
    auto& loaded=files;
    return loaded[index];
}
std::int32_t PlayerRecord::starting_configuration(std::int32_t index) {
    switch(index) {
    case 0:
    default:return field_0c_value();
    case 1:return field_14_value();
    case 2:return field_10_value();
    case 3:return field_18_value();
    }
}
std::int32_t PlayerRecord::field_0c_value() {return field_0c;}
std::int32_t PlayerRecord::field_18_value() {return field_18;}
void Animation::set_position(const Vector3& value) {vector_5bc=value;}
void Animation::stop() {
    base.field_28=-1;
    base.flags.bit_10=0;
}
}
