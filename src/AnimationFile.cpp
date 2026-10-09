#include "AnimationFile.hpp"
namespace th20 {
AnimationFile::AnimationFile()
    : id(0), bytes(nullptr), templates(nullptr), texture_count(0), script_count(0),
      sprite_count(0), sprites(nullptr), scripts(nullptr), textures(nullptr), stage(0),
      field_60(0), field_64(0), field_68(0), field_6c(0) {}
void AnimationFile::bind_animation(Animation* animation,std::int32_t script) {
    bind_animation(animation,script,nullptr);
}
}
