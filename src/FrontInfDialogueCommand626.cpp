#include "FrontInfDialogueCommand626.hpp"
#include "FrontDialogueAllocate156.hpp"
#include "FrontDialogueFieldViews.hpp"
#include "FrontDialogueRelease97.hpp"
#include "DialogueText.hpp"
#include "AnimationFile.hpp"
#include "Card.hpp"
#include "GameController.hpp"
#include "HudGauge.hpp"
#include "Session.hpp"
#include "SoundInf.hpp"
#include "DiagnosticAllocator.hpp"
#include <cstdint>
#include <cstring>

namespace th20 {

extern std::uint8_t* native_front_dialogue_voice_table_5c6110;
extern const char front_dialogue_allocator_label_5706f8[];

void NativeFrontInfDialogueCommandView::set_dialogue_command_4b9740(std::int32_t command) {
    if (command == -1 || command == -3) {
        const std::int32_t selector = command == -1;
        if (session.field_70_is_two() && !reinterpret_cast<NativeGameControllerRestartView*>(current_game_controller)->is_restarting_488830()) {
            const std::uint8_t* table = native_front_dialogue_voice_table_5c6110;
            const char* voice_name = *reinterpret_cast<const char* const*>(table + 0x0c + selector * 4);
            char track_name[0x100];
            strcpy_s(track_name, sizeof(track_name), voice_name);
            strcat_s(track_name, sizeof(track_name), ".wav");
            auto* sound_view = reinterpret_cast<NativeSoundInfQueuedTrackView*>(&process_sound);
            if (std::strcmp(sound_view->queued_track_name_4b8090(), track_name) == 0)
                return;
        }

        const std::int32_t sound_id = *reinterpret_cast<const std::int32_t*>(
            native_front_dialogue_voice_table_5c6110 + 0x58 + selector * 4);
        play_front_dialogue_voice_4d9b50(selector, sound_id);
        auto* file = reinterpret_cast<NativeFrontInfMessageFileView*>(this)->message_file_4b8270();
        file->spawn(nullptr, selector + 1, -1, nullptr);
        return;
    }

    if (command == -2) {
        Card* card = session.contexts[0].card_owner;
        if (reinterpret_cast<NativeCardExtraSoundView*>(card)->requires_extra_sound_488880())
            native_screen_dialogue_transition_5c60bc->finish_dialogue_4e5bd0();
        else
            reinterpret_cast<NativeGameControllerDialogueTransitionView*>(current_game_controller)->finish_dialogue_4bc570();
        return;
    }

    auto** dialogue_slot = reinterpret_cast<Dialogue**>(reinterpret_cast<std::uint8_t*>(this) + 0x1bc);
    if (*dialogue_slot)
        reinterpret_cast<NativeFrontDialogueReleaseView*>(this)->release_dialogue(*dialogue_slot);

    auto* allocator = reinterpret_cast<NativeDialogueFactoryView*>(process_allocator);
    *dialogue_slot = allocator->allocate_dialogue(front_dialogue_allocator_label_5706f8,
        reinterpret_cast<std::uint8_t*>(static_cast<std::uintptr_t>(command)));
}

} // namespace th20
