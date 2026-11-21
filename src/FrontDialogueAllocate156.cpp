#include "FrontDialogueAllocate156.hpp"
#include "DialogueText.hpp"
#include "NativeScreenFactoryViews.hpp"
#include <new>
#include <utility>

namespace th20 {

// Preserve the native out-of-line std::move<unsigned char*&> helper at 0x0040B280.
template __declspec(noinline) std::uint8_t*&&
    std::move<std::uint8_t*&>(std::uint8_t*&) noexcept;

Dialogue* NativeDialogueFactoryView::allocate_dialogue(
    const char*, std::uint8_t* script) {
    void* memory = ::operator new(sizeof(Dialogue));
    if (memory == nullptr)
        return nullptr;
    reinterpret_cast<NativeScreenMemoryView*>(memory)->clear_40c080(sizeof(Dialogue));
    return new (memory) Dialogue(std::move(script));
}

} // namespace th20
