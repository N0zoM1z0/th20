#include "SceneResources.hpp"

namespace th20 {

int initialize_shared_scene_resources() {
    if (scene_resources::initialize_hud() != 0) return -1;
    if (scene_resources::create_effects(0) == nullptr) return -1;
    if (scene_resources::create_weapon_stone(0) == nullptr) return -1;
    if (scene_resources::create_stone_menu(0) == nullptr) return -1;
    if (scene_resources::optional_step() != 0) return -1;
    if (scene_resources::optional_step() != 0) return -1;
    if (scene_resources::initialize_trophies() != 0) return -1;
    if (scene_resources::optional_step() != 0) return -1;
    return 0;
}

int release_shared_scene_resources() {
    scene_resources::release_effects(0);
    scene_resources::release_weapon_stone(0);
    scene_resources::release_stone_menu(0);
    scene_resources::release_hud();
    scene_resources::optional_step();
    scene_resources::optional_step();
    scene_resources::release_trophies();
    scene_resources::optional_step();
    return 0;
}

} // namespace th20
