// Entire original 332-byte Player bullet-graze feedback state machine.
// Three native side-effect scopes preserve actual MSVC i386 ownership and
// natural post-call NOPs; no manual padding, fake return or shortened body.
#include "Player.hpp"
#include "PlayerRecord.hpp"
#include "ItemResourceOwners.hpp"
#include "EnemyController.hpp"
#include "Context.hpp"
#include "Session.hpp"
#include "GameRandom.hpp"
#include "WeaponStoneInfo.hpp"
#include "SoundInf.hpp"
#include "EffectParameters.hpp"

namespace th20 {
extern GameRandom process_bullet_random;
void Player::record_bullet_graze(const Vector3& location, std::uint32_t bullet_color) {
    {
        context->player_record()->add_field_e4(1);
    }
    EffectParameters effect;
    effect.vector_00 = location;
    effect.color = bullet_color;
    *(reinterpret_cast<std::uint8_t*>(&effect.color.value) + 3) = 0xff;
    {
        context->effect_info()->queue_effect(process_bullet_random.next() % 4u,4,effect,0);
    }
    WeaponStoneInfo* stones=weapon_stone_info(0);
    std::int32_t amount;
    if (stone_enemy_controller()->byte_b0_value()) amount=1500;
    else amount=1000;
    stones->record_damage(&location, amount, 13);
    std::int32_t reward;
    if (enemy_controller(0)->graze_reward_active()) reward=50;
    else reward=10;
    {
        const std::int32_t reward_amount = reward;
        player_record(0)->add_field_44(reward_amount);
    }
    process_sound.request_effect_at(42,location.x);
}
}
