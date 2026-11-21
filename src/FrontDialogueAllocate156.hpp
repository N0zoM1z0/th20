#pragma once
#include <cstdint>

namespace th20 {

class Dialogue;

// Borrowed view of the allocator receiver used by the native Dialogue factory.
struct NativeDialogueFactoryView {
    Dialogue* allocate_dialogue(const char* diagnostic, std::uint8_t* script);
};

} // namespace th20
