#pragma once
#include "AnimationFile.hpp"

namespace th20 {
// Native 83B game AnimationFile wrapper for the original particle scripts.
// Borrowed class view; the genuine base owns file storage and lifetimes.
struct NativeParticleSpawnFileView : AnimationFile {
    AnimationHandle spawn_45d210(const char* expected_stem,
        std::int32_t script, const Vector3* position, float rotation,
        std::int32_t special);
};
}
