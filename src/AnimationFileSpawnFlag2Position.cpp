#include "AnimationFile.hpp"

namespace th20 {

AnimationHandle AnimationFile::spawn_flag2_position(
    const char* expected_stem, std::int32_t script, const Vector3& position,
    float rotation, std::int32_t layer, Animation** output) {
    return spawn(expected_stem, script, &position, rotation, layer, 2, output);
}

} // namespace th20
