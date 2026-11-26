// Complete native Card start at 0x00487C30: 1,896B, 62 calls and 26
// HIGHLOW fields. Preserve the temporary capture/zero-position lifetimes,
// live script-table reads and their indexed three-word descriptors.
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

// CORE/RECON-1188: the original 102B std::function constructor and 65B
// _Reset each make an out-of-line std::forward<T> call to the shared 8B
// identity leaf. Preserve the exact callable specialization rather than
// letting current MSVC inline this constexpr reference cast.
template __declspec(noinline) th20::NativeCardTextPayload&&
std::forward<th20::NativeCardTextPayload>(th20::NativeCardTextPayload&) noexcept;

namespace th20 {
// This borrowed view uses the independently whole-exact 42B BombController
// predicate; no new BombController base/class is introduced.
struct NativeCardStartBombView { bool active_478130() const; };

// The original table is reached through the process-owned pointer at
// 0x005C6110; it has a 0x34-byte group stride and 0x0C-byte subrecords.
// The temporary view below does not assert ownership or a larger class ABI.
extern const std::uint8_t* native_card_script_table_5c6110;

// Each native descriptor is three indexed int32 words: file id, script,
// then the group published to Card flag 9.
using NativeCardScriptEntry = std::int32_t[3];
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
        strcpy_s(reinterpret_cast<char*>(
                     reinterpret_cast<NativeSpellRecordArrayView*>(
                         reinterpret_cast<std::uint8_t*>(native_primary_records_50fc50(
                             native_card_records_5c6108))+0xB08)->record_486e10(index)),
                 0xC0,spell_name);
        auto* main_records = reinterpret_cast<NativeSpellRecordArrayView*>(
            reinterpret_cast<std::uint8_t*>(native_primary_records_50fc50(
                native_card_records_5c6108))+0xB08);
        main_records->record_486e10(index)->increment_attempt_488590(attempt_kind);

        // As with the primary record, retain the secondary archive/record
        // lookup as the first strcpy_s argument so native right-to-left
        // argument evaluation reproduces the original call ordering.
        strcpy_s(reinterpret_cast<char*>(
                     reinterpret_cast<NativeSpellRecordArrayView*>(
                         native_card_records_5c6108->secondary_488700()+0xB08)
                         ->record_486e10(index)),
                 0xC0,spell_name);
        auto* alternate = reinterpret_cast<NativeSpellRecordArrayView*>(
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
    // Its destructor is the penultimate native E8 at +0x746. The capture
    // is a temporary consumed by std::function; it is destroyed immediately
    // after enqueue, before sound and effect operations.
    std::pmr::string display_name(spell_name);
    reinterpret_cast<NativeCardAsciiTaskQueueView*>(native_card_renderer_5c0698)->
        enqueue_470180(std::function<void()>(NativeCardTextPayload(
            this,display_name,info_handles[1].resolve())));
    process_sound.request_effect(0x21,0);

    // The effect animation and its initial position are bound to the actual
    // Card context, not an invented globally-owned renderer structure.
    effect_handle=context->effect_info()->animation_file(0)->spawn("effect",6,-1,nullptr);
    if (context->enemy_controller()->selected(0)!=nullptr) position=context->enemy_controller()->selected(0)->position_ref();
    else {
        // List assignment constructs the native zero temporary, then copies
        // its three words from temporary storage into Card::position.
        position = {0.0f,0.0f,0.0f};
    }
    effect_handle.set_position(position);
    effect_handle.find_child(4,0)->variables().field_08=duration_frames;
    effect_handle.find_child(5,0)->variables().field_08=duration_frames;
    duration=duration_frames;

    // The original reads the clamped base before the player mode, then
    // applies the actual difficulty-dependent tier; not a constant reward.
    const std::int32_t reward_multipliers[5]={500000,1000000,1500000,2000000,1000000};
    const std::int32_t reward = static_cast<std::int32_t>(
        static_cast<std::uint32_t>(session.clamped_field_1f4()) *
        static_cast<std::uint32_t>(reward_multipliers[session.mode()]));
    bonus = reward;
    initial_bonus = reward;
    if (initial_bonus >= 1000000000)
        initial_bonus = 999999999;

    // The original issues this second named effect spawn independently.
    context->effect_info()->animation_file(0)->spawn("effect",0xD,-1,nullptr);

    // The real table at 0x005C6110 is mutable and re-read for *each*
    // original tested/spawned file id, script and flag-group word. The
    // macro expands the indexed word view seven times; caching
    // a local table entry suppresses five genuine original PE HIGHLOW roles.
    // Slots are 12B and each stage is 0x34B, with two main variants and
    // a separately optional third script. No helper E8 exists in the PE.
    const std::int32_t table_stage = group;
    const std::int32_t script_variant = (index >= 0x58 && index <= 0x5C) ? 1 : 0;
    if (CARD_SCRIPT_ENTRY(table_stage, script_variant)[0] >= 0) {
        auto* controller = enemy_controller(0);
        const std::uint32_t file_id =
            static_cast<std::uint32_t>(CARD_SCRIPT_ENTRY(table_stage, script_variant)[0]);
        auto* file = controller->animation_file(file_id);
        const std::int32_t script = CARD_SCRIPT_ENTRY(table_stage, script_variant)[1];
        background_handle = file->spawn(nullptr, script, -1, nullptr);
    }

    reinterpret_cast<NativeCardStartFlagsView*>(this)->set_spell_flag9_488960(
        static_cast<std::uint32_t>(CARD_SCRIPT_ENTRY(table_stage, script_variant)[2]));

    if (CARD_SCRIPT_ENTRY(group, 2)[0] != -1) {
        auto* controller = enemy_controller(0);
        const std::uint32_t file_id = static_cast<std::uint32_t>(
            CARD_SCRIPT_ENTRY(group, 2)[0]);
        auto* file = controller->animation_file(file_id);
        const std::int32_t script = CARD_SCRIPT_ENTRY(group, 2)[1];
        file->spawn(nullptr, script, -1, nullptr);
    }
}
#undef CARD_SCRIPT_ENTRY
}
