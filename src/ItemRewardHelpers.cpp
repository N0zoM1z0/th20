#include "ItemRewardHelpers.hpp"
#include "ItemRewardPopupQueue.hpp"
#include "Player.hpp"
#include "Session.hpp"
#include "SoundInf.hpp"
namespace th20 {
void __fastcall item_award_life_reward(Item* item) {
    if (player_record(0)->clamped_option_units()>=player_record(0)->clamped_option_cap()) {
        auto amount=player_record(0)->clamped_field_40();
        amount-=amount%10;
        if (amount<=0) amount=10;
        item_reward_popup_queue(0)->enqueue(&item->position,amount,0xff40ff40u);
        session.add_score(static_cast<std::uint32_t>(amount));
    }
    auto* record=player_record(0);
    const auto threshold=player_record(0)->clamped_option_cap();
    const std::int32_t threshold_crossed=record->add_field_30_and_check(threshold);
    if (threshold_crossed!=0) {
        player(0)->rebuild_option_animations(-1);
        item_reward_popup_queue(0)->enqueue(&item->position,-1,0xffffff40u);
        process_sound.request_effect_at(13,item->position.x);
    }
}
void __fastcall item_award_reward_type_1(Item* item) {
    std::int32_t popup_amount;
    const std::int32_t base_amount=player_record(0)->clamped_field_40()/2+
        (player_record(0)->clamped_field_44()*player_record(0)->clamped_field_40())/
            player_record(0)->clamped_field_48();
    const float item_y=item->position.y;
    if (player(0)->motion_parameter_10_value()>=item_y || item->state==3) {
        popup_amount=base_amount;
        popup_amount-=popup_amount%10;
        if (popup_amount<=0) popup_amount=10;
        item_reward_popup_queue(0)->enqueue(&item->position,popup_amount,0xffffff00u);
    } else {
        const std::int32_t nine_tenths_left=(base_amount*9)/10;
        const std::int32_t nine_tenths_right=(base_amount*9)/10;
        const std::int32_t distance=static_cast<std::int32_t>(item_y-player(0)->motion_parameter_10_value());
        popup_amount=nine_tenths_left-(nine_tenths_right*distance)/450;
        popup_amount-=popup_amount%10;
        if (popup_amount<=0) popup_amount=10;
        item_reward_popup_queue(0)->enqueue(&item->position,popup_amount,0xffffffffu);
    }
    player_record(0)->add_score(static_cast<std::uint64_t>(popup_amount));
    player_record(0)->add_field_3c_clamped(1);
}
void __fastcall item_award_reward_type_0(Item* item) {
    const float player_y=player(0)->position_ref().y;
    std::int32_t amount;
    if (player_record(0)->clamped_option_units()>=player_record(0)->clamped_option_cap()) {
        if (player_y<=player(0)->motion_parameter_10_value() || item->state==3) {
            amount=player_record(0)->clamped_field_40();
            amount-=amount%10;
            if (amount<=0) amount=10;
        } else {
            const auto first=player_record(0)->clamped_field_40();
            const auto second=player_record(0)->clamped_field_40();
            const auto distance=static_cast<std::int32_t>(player_y)-
                static_cast<std::int32_t>(player(0)->motion_parameter_10_value());
            amount=(first*9)/10-(((second*9)/10)*distance)/450;
            amount-=amount%10;
            if (amount<=0) amount=10;
        }
        item_reward_popup_queue(0)->enqueue(&item->position,amount,0xffffffffu);
    } else {
        amount=100;
        if (player_record(0)->add_field_30_and_check(1)) {
            player(0)->rebuild_option_animations(-1);
            item_reward_popup_queue(0)->enqueue(&item->position,-1,0xffffff40u);
            process_sound.request_effect_at(13,item->position.x);
        }
    }
    session.add_score(static_cast<std::uint32_t>(amount));
}
void __fastcall item_award_reward_type_2(Item* item) {
    std::int32_t amount;
    if (item->context->player_record()->clamped_option_units()>=item->context->player_record()->clamped_option_cap()) {
        amount=20000;
        session.add_score(static_cast<std::uint32_t>(amount));
        auto* queue=reinterpret_cast<ItemRewardPopupQueue*>(
            reinterpret_cast<Player*>(item->context)->animation_file_ref());
        queue->enqueue(&item->position,amount,0xff808080u);
        process_sound.request_effect_at(13,item->position.x);
    } else {
        amount=100;
        auto* record=item->context->player_record();
        const auto starting=item->context->player_record()->starting_power();
        const std::int32_t threshold_crossed=record->add_field_30_and_check(starting);
        if (threshold_crossed!=0) {
            item->context->player()->rebuild_option_animations(-1);
            process_sound.request_effect_at(13,item->position.x);
            auto* queue=reinterpret_cast<ItemRewardPopupQueue*>(
                reinterpret_cast<Player*>(item->context)->animation_file_ref());
            queue->enqueue(&item->position,-1,0xffffff40u);
        }
    }
    session.add_score(static_cast<std::uint32_t>(amount));
}
}
