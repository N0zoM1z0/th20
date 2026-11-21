#pragma once

namespace th20 {

class Dialogue;

struct NativeFrontDialogueReleaseView {
    void release_dialogue(Dialogue* dialogue);
};

} // namespace th20
