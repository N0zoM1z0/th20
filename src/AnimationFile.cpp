#include "AnimationFile.hpp"
#include "DiagnosticObjectFactories.hpp"
namespace th20 {
TextureRecord::TextureRecord() noexcept : texture(nullptr), external_bytes(nullptr), external_size(0),
    bytes_per_pixel(0), header(nullptr), flags{} {}
SpriteData::SpriteData() noexcept : file_id(0),texture_index(0),texture_id(0),left(0),top(0),right(0),bottom(0),
    extent_1c(0),extent_20(0),field_24(0),field_28(0),field_2c(0),field_30(0),field_34(0),
    u0(0),v0(0),u1(0),v1(0),extent_48(0),extent_4c(0),scale_50(0),scale_54(0) {}
AnimationFile::AnimationFile()
    : id(0), bytes(nullptr), templates(nullptr), texture_count(0), script_count(0),
      sprite_count(0), sprites(nullptr), scripts(nullptr), textures(nullptr), stage(0),
      field_60(0), field_64(0), field_68(0), field_6c(0) {}
void AnimationFile::bind_animation(Animation* animation,std::int32_t script) {
    bind_animation(animation,script,nullptr);
}
std::uint32_t AnimationFile::texture_id(std::uint32_t index) { return (id<<8)|index; }
void AnimationFile::store_sprite(std::int32_t index,const SpriteData& source) {
    sprites[index] = source;
    sprites[index].u0 = sprites[index].left / sprites[index].extent_20;
    sprites[index].u1 = sprites[index].right / sprites[index].extent_20;
    sprites[index].v0 = sprites[index].top / sprites[index].extent_1c;
    sprites[index].v1 = sprites[index].bottom / sprites[index].extent_1c;
    sprites[index].extent_4c = (sprites[index].right - sprites[index].left) / source.scale_50;
    sprites[index].extent_48 = (sprites[index].bottom - sprites[index].top) / source.scale_54;
}
template AnimationFile* DiagnosticAllocator::allocate_object<AnimationFile>(const char*);
}
