#pragma once
#include "AnimationHandle.hpp"
#include "Vector3.hpp"
#include <atomic>
#include <memory_resource>
#include <string>
namespace th20 {
struct Animation;
struct SpriteData;
struct TextureRecord;
struct AnmInstruction;
struct AnimationFile {
    std::uint32_t id;
    std::pmr::string filename, stem;
    std::uint8_t* bytes;
    Animation* templates;
    std::int32_t texture_count;
    std::uint32_t script_count, sprite_count;
    SpriteData* sprites;
    AnmInstruction** scripts;
    TextureRecord* textures;
    std::atomic<std::uint32_t> stage;
    std::uint32_t field_60, field_64, field_68, field_6c;
    AnimationFile();
    ~AnimationFile();
    void bind_animation(Animation* animation, std::int32_t script);
    // Original parent/VM binding remains a genuine undefined interface.
    void bind_animation(Animation* animation, std::int32_t script, Animation* parent);
    AnimationHandle spawn(const char* expected_stem, std::int32_t script,
                          const Vector3& position, float rotation,
                          std::int32_t layer, std::uint32_t flags);
};
#if defined(_M_IX86)
static_assert(sizeof(AnimationFile)==0x70);
static_assert(offsetof(AnimationFile,stage)==0x5c);
#endif
}
