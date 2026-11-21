#include "FrontDialogueAllocate156.hpp"
#include "DialogueText.hpp"
#include <cstring>
#include <new>
#include <utility>

namespace th20 {

Dialogue* NativeDialogueFactoryView::allocate_dialogue(const char*, std::uint8_t* script) {
    void* storage = ::operator new(sizeof(Dialogue), std::nothrow);
    if (!storage)
        return nullptr;
    std::memset(storage, 0, sizeof(Dialogue));
    return new (storage) Dialogue(std::move(script));
}

} // namespace th20
