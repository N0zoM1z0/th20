#pragma once

namespace th20 {

class EffectInfo;
class WeaponStoneInfo;
class StoneMenuInfo;

namespace scene_resources {
// These independently observed native interfaces remain undefined until their
// owning subsystems are reconstructed. Pointer return types do not define layout.
int initialize_hud();
EffectInfo* create_effects(int view);
WeaponStoneInfo* create_weapon_stone(int view);
StoneMenuInfo* create_stone_menu(int view);
int optional_step(); // Observed native helper returns zero; source identity open.
int initialize_trophies();
void release_effects(int view);
void release_weapon_stone(int view);
// The native caller passes zero; the current native callee does not read it.
void release_stone_menu(int view);
int release_hud();
int release_trophies();
} // namespace scene_resources

int initialize_shared_scene_resources();
int release_shared_scene_resources();

} // namespace th20
