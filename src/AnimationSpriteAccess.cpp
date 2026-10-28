#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "AnimationRuntimeOwner.hpp"

namespace th20 {
// Original Animation+0x1C file identity goes through the real Renderer
// manager interface. The owner layout remains unknown: use its true ABI.
AnimationFile* Animation::animation_file() {
    return current_animation_pool->file_by_index(base.field_1c);
}

// Native SpriteData storage belongs to the existing 0x70-byte AnimationFile;
// the original sprite element is 0x58 bytes, not a fabricated prefix.
SpriteData* AnimationFile::sprite(std::int32_t index) {
    return &sprites[index];
}

// Complete typed native Animation sprite lookup. The original script/sprite
// selector lives in AnimationBase+0x20 and uses the real file lookup above.
SpriteData* Animation::sprite_data() {
    AnimationFile* file = animation_file();
    const std::int32_t index = base.field_20;
    return file->sprite(index);
}
} // namespace th20
