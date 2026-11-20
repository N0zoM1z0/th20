#include "Item.hpp"
#include "ItemRewardPopupQueue.hpp"
#include "Player.hpp"
#include "Session.hpp"
#include "SoundInf.hpp"
namespace th20 {
void Item::award_life_reward() {
    if (player_record(0)->clamped_option_units()>=player_record(0)->clamped_option_cap()) {
        auto amount=player_record(0)->clamped_field_40();
        amount-=amount%10;
        if (amount<=0) amount=10;
        item_reward_popup_queue(0)->enqueue(&position,amount,0xff40ff40u);
        session.add_score(static_cast<std::uint32_t>(amount));
    }
    auto* record=player_record(0);
    const auto threshold=player_record(0)->clamped_option_cap();
    const std::int32_t threshold_crossed=record->add_field_30_and_check(threshold);
    if (threshold_crossed!=0) {
        player(0)->rebuild_option_animations(-1);
        item_reward_popup_queue(0)->enqueue(&position,-1,0xffffff40u);
        process_sound.request_effect_at(13,position.x);
    }
}
}
