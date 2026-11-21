#pragma once
#include <cstdint>

namespace th20 {

class Card;

void play_front_dialogue_voice_4d9b50(std::int32_t selector, std::int32_t sound_id);

struct NativeCardExtraSoundView {
    bool requires_extra_sound_488880();
};

struct NativeGameControllerRestartView {
    bool is_restarting_488830();
};

struct NativeGameControllerDialogueTransitionView {
    void finish_dialogue_4bc570();
};

struct NativeScreenDialogueTransitionView {
    void finish_dialogue_4e5bd0();
};

extern NativeScreenDialogueTransitionView* native_screen_dialogue_transition_5c60bc;

struct NativeFrontInfDialogueCommandView {
    void set_dialogue_command_4b9740(std::int32_t command);
};

} // namespace th20
