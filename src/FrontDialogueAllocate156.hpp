#pragma once
#include <cstdint>

namespace th20 {

class Dialogue;

struct NativeDialogueFactoryView {
    Dialogue* allocate_dialogue(const char* diagnostic, std::uint8_t* script);
};

} // namespace th20
