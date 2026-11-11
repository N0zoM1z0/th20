// Original Card start 1,896B Boss: main gameplay stages reconstructed
// as typed C++20. The genuine renderer-file/text-file getters and all
// seven script-table global reads now recover all original 62 E8/26
// HIGHLOW destination roles in order. Candidate 1848B remains NONEXACT;
// PMR callable construction and original EH/local lifetimes remain open.
// The retained TextJob/record table interfaces below remain provisional,
// and must be independently resolved before whole-code acceptance.
#include "Card.hpp"
#include "NativeCardStartFlagsView.hpp"
#include "NativeCardFinishViews.hpp"
#include "NativeCardRendererFileView.hpp"
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

// Deliberately re-evaluate the native global table pointer at each of
// its seven actual uses; no artificial cached table snapshot.
#define CARD_SCRIPT_ENTRY(stage,option) (*reinterpret_cast<const NativeCardScriptEntry*>(native_card_script_table_5c6110+0x64+(stage)*0x34+(option)*0xC))

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

    // The first and third handles read the live AsciiInf/current renderer
    // resource via its original 20B member getter. The text handle instead
    // uses the 16B getter for the independent shared text-file owner.
    // All three reads and spawns are independent original E8 calls.
    info_handles[0] = native_card_renderer_5c0698->current_file_437950()->spawn(
        nullptr,0,-1,nullptr);
    info_handles[1] = reinterpret_cast<AsciiInf*>(native_card_renderer_5c0698)
        ->text_animation_file()->spawn("text",player_index+0x16,-1,nullptr);
    info_handles[2] = native_card_renderer_5c0698->current_file_437950()->spawn(
        nullptr,1,-1,nullptr);

    // The original PMR display name outlives its captured text payload,
    // the queue submission and the subsequent Card effect/script spawns.
    // Its own destructor is the penultimate native E8 at +0x746, not an
    // early cleanup before the sound effect and reward update.
    // The actual 56B/23B capture constructor/destructor, 64B move and
    // 167B PMR copy constructor are independently whole exact; the queue's own
    // std::function capture/move EH remains a separate unresolved owner.
    std::pmr::string display_name(spell_name);
    {
        NativeCardTextPayload payload(this,display_name,
                                     info_handles[1].resolve());
        reinterpret_cast<NativeCardAsciiTaskQueueView*>(native_card_renderer_5c0698)->
            enqueue_470180(std::function<void()>(std::move(payload)));
    }
    process_sound.request_effect(0x21,0);

    // The effect animation and its initial position are bound to the actual
    // Card context, not an invented globally-owned renderer structure.
    auto* effect_file=context->effect_info()->animation_file(0);
    effect_handle=effect_file->spawn("effect",6,-1,nullptr);
    auto* boss=context->enemy_controller()->selected(0);
    if (boss!=nullptr) position=context->enemy_controller()->selected(0)->position_ref();
    else position=Vector3(0.0f,0.0f,0.0f);
    effect_handle.set_position(position);
    auto* var4=effect_handle.find_child(4,0);
    var4->variables().field_08=duration_frames;
    auto* var5=effect_handle.find_child(5,0);
    var5->variables().field_08=duration_frames;
    duration=duration_frames;

    // The original reads the clamped base before the player mode, then
    // applies the actual difficulty-dependent tier; not a constant reward.
    const std::int32_t reward_multipliers[5]={500000,1000000,1500000,2000000,1000000};
    const std::int32_t base=session.clamped_field_1f4();
    std::int32_t multiplier_index=session.mode();
    const std::uint32_t raw_bonus=static_cast<std::uint32_t>(base)*
        static_cast<std::uint32_t>(reward_multipliers[multiplier_index]);
    bonus=static_cast<std::int32_t>(raw_bonus);
    initial_bonus=bonus>999999999 ? 999999999 : bonus;

    // The original issues this second named effect spawn independently.
    effect_file=context->effect_info()->animation_file(0);
    effect_file->spawn("effect",0xD,-1,nullptr);

    // The real table at 0x005C6110 is mutable and re-read for *each*
    // original tested/spawned file id, script and flag-group word. The
    // macro expands actual typed pointer expressions seven times; caching
    // a local table entry suppresses five genuine original PE HIGHLOW roles.
    // Slots are 12B and each stage is 0x34B, with two main variants and
    // a separately optional third script. No helper E8 exists in the PE.
    const std::int32_t variant=(index>=0x58 && index<=0x5C)?1:0;
    if (CARD_SCRIPT_ENTRY(group,variant).file_id>=0) {
        auto* file=enemy_controller(0)->animation_file(CARD_SCRIPT_ENTRY(group,variant).file_id);
        background_handle=file->spawn(nullptr,CARD_SCRIPT_ENTRY(group,variant).script,-1,nullptr);
    }
    reinterpret_cast<NativeCardStartFlagsView*>(this)->set_spell_flag9_488960(
        static_cast<std::uint32_t>(CARD_SCRIPT_ENTRY(group,variant).group));

    if (CARD_SCRIPT_ENTRY(group,2).file_id!=-1) {
        auto* file=enemy_controller(0)->animation_file(CARD_SCRIPT_ENTRY(group,2).file_id);
        file->spawn(nullptr,CARD_SCRIPT_ENTRY(group,2).script,-1,nullptr);
    }
}
#undef CARD_SCRIPT_ENTRY
}
