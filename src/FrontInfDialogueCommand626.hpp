#pragma once

#include "FrontDialogueAllocate156.hpp"
#include "FrontDialogueFieldViews.hpp"
#include "FrontDialogueRelease97.hpp"
#include "GameController.hpp"
#include "NativeCardFinishViews.hpp"
#include "HudGauge.hpp"
#include "NativeCardFinishViews.hpp"
#include <cstdint>

namespace th20 {

struct NativeGameControllerDialogueTransitionView {
    void finish_dialogue_4bc570();
};

struct NativeScreenDialogueTransitionView {
    void finish_dialogue_4e5bd0();
};

extern NativeScreenDialogueTransitionView* native_screen_dialogue_transition_5c60bc;
extern const char front_dialogue_allocator_label_5706f8[];
extern const std::uint8_t* native_card_script_table_5c6110;

} // namespace th20
