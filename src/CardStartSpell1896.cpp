// Original Card start 1,896B boss: main gameplay stages reconstructed
// as a typed, compilable C++ research candidate. NONEXACT: original 62 E8,
// 26 PE HIGHLOW, native PMR string/text task EH and live resource owners.
// The retained TextJob/record table interfaces below remain provisional,
// and must be independently resolved before whole-code acceptance.
#include "Card.hpp"
#include "NativeCardStartFlagsView.hpp"
#include "NativeCardFinishViews.hpp"
#include "NativeCardSpellViews.hpp"
#include "NativeCardTextPayload.hpp"
#include "NativeCardAsciiTaskQueueView.hpp"
#include "Bomb.hpp"
#include "EnemyController.hpp"
#include "Enemy.hpp"
#include "ItemResourceOwners.hpp"
#include "TextLine.hpp"
#include "SoundInf.hpp"
#include "Animation.hpp"
#include "AnmVariables.hpp"
#include "AnimationFile.hpp"
#include <cstdint>
#include <cstring>
#include <functional>
#include <utility>
#include <memory_resource>
#include <string>

namespace th20 {
// This borrowed view uses the independently whole-exact 42B BombController
// predicate; no new BombController base/class is introduced.
struct NativeCardStartBombView { bool active_478130() const; };

// The original table is reached through the process-owned pointer at
// 0x005C6110; it has a 0x34-byte group stride and 0x0C-byte subrecords.
// The temporary view below does not assert ownership or a larger class ABI.
extern const std::uint8_t* native_card_script_table_5c6110;

struct NativeCardScriptEntry {
    std::int32_t file_id;
    std::int32_t group;
    std::int32_t script;
};
static_assert(sizeof(NativeCardScriptEntry)==0xC);

static const NativeCardScriptEntry& spell_script_entry(
    std::int32_t group, std::int32_t variant) {
    return *reinterpret_cast<const NativeCardScriptEntry*>(
        native_card_script_table_5c6110+0x64+group*0x34+variant*0xC);
}

void Card::start_spell(std::int32_t index, const char* spell_name,
                       std::int32_t duration_frames, std::int32_t group) {
    age = 0;
    spell_index = index;
    strcpy_s(name, sizeof(name), spell_name);

    spell_flags.bits |= 1u;
    spell_flags.bits |= 2u;
    spell_flags.bits &= ~8u;
    spell_flags.bits &= ~16u;
    spell_flags.bits |= 0x200u;
    reinterpret_cast<NativeCardStartFlagsView*>(this)->clear_capture_effect_flag_4888c0();

    if (!native_card_play_5c60fc->is_paused_488800()) {
        const std::int32_t attempt_kind = session.field_70_is_two() ? 1 : 0;
        auto* main_records = reinterpret_cast<NativeSpellRecordArrayView*>(
            reinterpret_cast<std::uint8_t*>(native_primary_records_50fc50(
                native_card_records_5c6108))+0xB08);
        auto* first = main_records->record_486e10(index);
        strcpy_s(reinterpret_cast<char*>(first),0xC0,spell_name);
        main_records = reinterpret_cast<NativeSpellRecordArrayView*>(
            reinterpret_cast<std::uint8_t*>(native_primary_records_50fc50(
                native_card_records_5c6108))+0xB08);
        main_records->record_486e10(index)->increment_attempt_488590(attempt_kind);

        auto* alternate = reinterpret_cast<NativeSpellRecordArrayView*>(
            native_card_records_5c6108->secondary_488700()+0xB08);
        strcpy_s(reinterpret_cast<char*>(alternate->record_486e10(index)),0xC0,
                 spell_name);
        alternate = reinterpret_cast<NativeSpellRecordArrayView*>(
            native_card_records_5c6108->secondary_488700()+0xB08);
        alternate->record_486e10(index)->increment_attempt_488590(attempt_kind);
    }

    native_card_hud_5c06a4->start_spell_effects_488a60();
    spell_flags.bits &= ~0x20u;
    if (reinterpret_cast<NativeCardStartBombView*>(bomb_controller(0))->active_478130())
        spell_flags.bits |= 0x20u;
    frames = 1;
    spell_flags.bits &= ~0x40u;

    // Three genuine Card info handles, each with independent native creation.
    auto* text_file = current_ascii->animation_file;
    info_handles[0] = text_file->spawn(nullptr,0,-1,nullptr);
    info_handles[1] = text_file->spawn(nullptr,player_index+0x16,-1,nullptr);
    info_handles[2] = text_file->spawn(nullptr,1,-1,nullptr);

    // Original retains a local PMR string and builds a separate task using
    // this Card, the name, and the second animation's resolved VM object.
    // The actual 56B/23B capture constructor/destructor, 64B move and
    // 167B PMR copy constructor are independently whole exact; the queue's own
    // std::function capture/move EH remains a separate unresolved owner.
    {
        std::pmr::string display_name(spell_name);
        NativeCardTextPayload payload(this,display_name,
                                     info_handles[1].resolve());
        reinterpret_cast<NativeCardAsciiTaskQueueView*>(current_ascii)->
            enqueue_470180(std::function<void()>(std::move(payload)));
    }
    process_sound.request_effect(0x21,0);

    // The effect animation and its initial position are bound to the actual
    // Card context, not an invented globally-owned renderer structure.
    auto* effect_file=context->effect_info()->animation_file(0);
    effect_handle=effect_file->spawn("effect",6,-1,nullptr);
    auto* boss=context->enemy_controller()->selected(0);
    if (boss==nullptr) position=Vector3(0.0f,0.0f,0.0f);
    else position=context->enemy_controller()->selected(0)->position_ref();
    effect_handle.set_position(position);
    auto* var4=effect_handle.find_child(4,0);
    var4->variables().field_08=duration_frames;
    auto* var5=effect_handle.find_child(5,0);
    var5->variables().field_08=duration_frames;
    duration=duration_frames;

    // This table and the signed multiplication represent the game's five
    // difficulty-dependent reward tiers, not a constant score credit.
    const std::int32_t reward_multipliers[5]={500000,1000000,1500000,2000000,1000000};
    std::int32_t multiplier_index=session.mode();
    const std::int32_t base=session.clamped_field_1f4();
    const std::uint32_t raw_bonus=static_cast<std::uint32_t>(base)*
        static_cast<std::uint32_t>(reward_multipliers[multiplier_index]);
    bonus=static_cast<std::int32_t>(raw_bonus);
    initial_bonus=bonus>999999999 ? 999999999 : bonus;

    // The original issues this second named effect spawn independently.
    effect_file=context->effect_info()->animation_file(0);
    effect_file->spawn("effect",0xD,-1,nullptr);

    // The original stage profile uses two 12-byte columns for Card indexes
    // 0x58..0x5C and a fixed third column for a further optional animation.
    const std::int32_t variant=(index>=0x58 && index<=0x5C)?1:0;
    const auto& primary=spell_script_entry(group,variant);
    if (primary.file_id>=0) {
        auto* file=enemy_controller(0)->animation_file(primary.file_id);
        background_handle=file->spawn(nullptr,primary.script,-1,nullptr);
    }
    reinterpret_cast<NativeCardStartFlagsView*>(this)->set_spell_flag9_488960(
        static_cast<std::uint32_t>(primary.group));

    const auto& optional=spell_script_entry(group,2);
    if (optional.file_id!=-1) {
        auto* file=enemy_controller(0)->animation_file(optional.file_id);
        file->spawn(nullptr,optional.script,-1,nullptr);
    }
}
}
