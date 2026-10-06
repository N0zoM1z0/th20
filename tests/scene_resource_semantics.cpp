#include "SceneResources.hpp"
#include <cassert>
#include <vector>

namespace {
std::vector<int> calls;
int failed_stage;
int pointer_token;
bool entered(int stage) { calls.push_back(stage); return failed_stage == stage; }
}

// Test-only observations for unresolved owners. Tokens are never dereferenced;
// this fixture establishes orchestration, not resource storage or OS lifetime.
namespace th20::scene_resources {
int initialize_hud() { calls.push_back(0); return 0; }
EffectInfo* create_effects(int view) {
    assert(view == 0);
    return entered(1) ? nullptr : reinterpret_cast<EffectInfo*>(&pointer_token);
}
WeaponStoneInfo* create_weapon_stone(int view) {
    assert(view == 0);
    return entered(2) ? nullptr : reinterpret_cast<WeaponStoneInfo*>(&pointer_token);
}
StoneMenuInfo* create_stone_menu(int view) {
    assert(view == 0);
    return entered(3) ? nullptr : reinterpret_cast<StoneMenuInfo*>(&pointer_token);
}
int optional_step() { calls.push_back(4); return 0; }
int initialize_trophies() { return entered(5) ? -1 : 0; }
void release_effects(int view) { assert(view == 0); calls.push_back(6); }
void release_weapon_stone(int view) { assert(view == 0); calls.push_back(7); }
void release_stone_menu(int view) { assert(view == 0); calls.push_back(8); }
int release_hud() { calls.push_back(9); return 0; }
int release_trophies() { calls.push_back(10); return 0; }
}

void check_scene_resource_protocol() {
    failed_stage = -1;
    calls.clear();
    assert(th20::initialize_shared_scene_resources() == 0);
    assert((calls == std::vector<int>{0,1,2,3,4,4,5,4}));
    for (int stage : {1,2,3,5}) {
        failed_stage = stage;
        calls.clear();
        assert(th20::initialize_shared_scene_resources() == -1);
        const auto expected = stage == 1 ? std::vector<int>{0,1} :
                              stage == 2 ? std::vector<int>{0,1,2} :
                              stage == 3 ? std::vector<int>{0,1,2,3} :
                                           std::vector<int>{0,1,2,3,4,4,5};
        assert(calls == expected); // No later acquisition or rollback on failure.
    }
    calls.clear();
    assert(th20::release_shared_scene_resources() == 0);
    assert((calls == std::vector<int>{6,7,8,9,4,4,10,4}));
}
