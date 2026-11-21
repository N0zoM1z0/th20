#include "FrontDialogueRelease97.hpp"
#include "DialogueText.hpp"
#include "LockRegistry.hpp"
#include <mutex>
#include <memory>

namespace th20 {

void NativeFrontDialogueReleaseView::release_dialogue(Dialogue* dialogue) {
    if (dialogue == nullptr)
        return;
    std::destroy_at(dialogue);
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(1));
    ::operator delete(dialogue);
}

} // namespace th20
