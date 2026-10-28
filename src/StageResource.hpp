#pragma once

namespace th20 {
class AnimationFile;

// Native process pointer at 0x005C069C, shared with stage/background callers.
// The original class and member spelling remain unproved. Only its observed
// thiscall at 0x004AADF0 is declared; no storage layout or body is fabricated.
struct StageResourceOwner {
    AnimationFile* animation_file();
};
extern StageResourceOwner* process_stage_resource;
}
