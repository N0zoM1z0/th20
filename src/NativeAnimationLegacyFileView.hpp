#pragma once

#include "Animation.hpp"
#include "AnimationFile.hpp"

namespace th20 {
// The original VM and AnimationHandle refresh path both resolve the file
// index stored at AnimationBase+0x18. This is deliberately distinct from
// Animation::animation_file(), which uses the sibling +0x1C index.
struct NativeAnimationLegacyFileView : Animation {
    AnimationFile* previous_file_437470();
};
} // namespace th20
