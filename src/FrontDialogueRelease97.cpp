#include "DialogueText.hpp"
#include "FrontDialogueRelease97.hpp"
#include "LockRegistry.hpp"
#include <memory>
#include <mutex>

namespace th20 {

void NativeFrontDialogueReleaseView::release_dialogue(Dialogue* dialogue) {
    if (!dialogue)
        return;
    std::destroy_at(dialogue);
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(1));
    ::operator delete(dialogue);
}

} // namespace th20
