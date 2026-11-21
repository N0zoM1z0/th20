#include "FrontInfDialogueCommand626.hpp"
#include "AnimationFile.hpp"
#include "Card.hpp"
#include "DiagnosticAllocator.hpp"
#include "DialogueText.hpp"
#include "Graphics.hpp"
#include "SecureCrt.hpp"
#include "Session.hpp"
#include "SoundInf.hpp"
#include <cstdint>
#include <cstring>

namespace th20 {

void FrontInf::set_dialogue_command_4b9740(std::int32_t command) {
    if (command == -1 || command == -3) {
        const std::int32_t selector = command == -1 ? 1 : 0;
        if (session.field_70_is_two() && current_game_controller->restart() == 0) {
            char queued_voice_path[0x100];
            strcpy_s(queued_voice_path, 0x100, *reinterpret_cast<const char* const*>(
                native_card_script_table_5c6110 + 0x0c + selector * 4));
            char* suffix = queued_voice_path + std::strlen(queued_voice_path);
            suffix[0] = '.';
            suffix[1] = 'w';
            suffix[2] = 'a';
            suffix[3] = 'v';
            suffix[4] = '\0';
            if (std::strcmp(reinterpret_cast<NativeSoundInfQueuedTrackView*>(&process_sound)
                    ->queued_track_name_4b8090(), queued_voice_path) == 0)
                return;
        }

        process_graphics.play_front_dialogue_voice_4d9b50(selector,
            *reinterpret_cast<const std::int32_t*>(
                native_card_script_table_5c6110 + 0x58 + selector * 4));
        auto* file = reinterpret_cast<NativeFrontInfMessageFileView*>(current_front)
            ->message_file_4b8270();
        file->spawn(nullptr, selector + 1, -1, nullptr);
        return;
    }

    if (command == -2) {
        if (reinterpret_cast<NativeCardEndFlagView*>(th20::card(0))
                ->requires_extra_sound_488880() != 0) {
            native_screen_dialogue_transition_5c60bc->finish_dialogue_4e5bd0();
        } else {
            reinterpret_cast<NativeGameControllerDialogueTransitionView*>(
                current_game_controller)->finish_dialogue_4bc570();
        }
        return;
    }

    if (has_dialogue()) {
        reinterpret_cast<NativeFrontDialogueReleaseView*>(process_allocator)->
            release_dialogue(dialogue);
        dialogue = nullptr;
        dialogue = nullptr;
    }
    dialogue = reinterpret_cast<NativeDialogueFactoryView*>(process_allocator)
        ->allocate_dialogue(front_dialogue_allocator_label_5706f8,
            message_bytes + *reinterpret_cast<const std::int32_t*>(
                message_bytes + command * 8 + 4));
    dialogue->state = command;
}

} // namespace th20
