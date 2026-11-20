#include "WeaponStoneInfo.hpp"
#include "Animation.hpp"

namespace th20 {
struct WeaponStoneProgressCallback {
    std::int32_t update(Animation* animation);
};
std::int32_t WeaponStoneProgressCallback::update(Animation*) {
    weapon_stone_info(0)->update_progress_mesh();
    return 0;
}
std::int32_t weapon_stone_progress_animation_callback(Animation* animation) {
    WeaponStoneProgressCallback callback;
    return callback.update(animation);
}
}
