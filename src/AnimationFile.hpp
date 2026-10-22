#pragma once
#include "AnimationHandle.hpp"
#include "Vector3.hpp"
#include <atomic>
#include <cstddef>
#include <memory_resource>
#include <string>
struct IDirect3DTexture9;
namespace th20 {
struct Animation;
struct AnmInstruction;
struct AnmHeader;
struct TextureRecordFlags { std::uint32_t bits; };
// GPU and external-image retirement belongs to Renderer/File clearing.
// Array storage release does not destroy either pointed-to resource.
struct TextureRecord {
    IDirect3DTexture9* texture;
    std::uint8_t* external_bytes;
    std::uint32_t external_size, bytes_per_pixel;
    AnmHeader* header;
    TextureRecordFlags flags;
    TextureRecord() noexcept;
};
struct SpriteData {
    std::uint32_t file_id, texture_index, texture_id;
    float left, top, right, bottom;
    float extent_1c, extent_20;
    // Independent construction and loading use float lanes for these values.
    float field_24, field_28, field_2c, field_30, field_34;
    float u0, v0, u1, v1;
    float extent_48, extent_4c, scale_50, scale_54;
    SpriteData() noexcept;
};
static_assert(sizeof(TextureRecordFlags)==4);
static_assert(sizeof(SpriteData)==0x58);
static_assert(offsetof(SpriteData,field_24)==0x24);
static_assert(offsetof(SpriteData,u0)==0x38);
static_assert(offsetof(SpriteData,scale_50)==0x50);
class AnimationFile {
public:
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
    AnmInstruction* script(std::int32_t index);
    std::uint32_t texture_id(std::uint32_t index);
    void store_sprite(std::int32_t index,const SpriteData& source);
    void apply_template(Animation* animation, std::int32_t script);
    AnimationFile();
    ~AnimationFile();
    // Loaded-resource retirement still requires the actual Renderer protocol.
    void clear();
    void bind_animation(Animation* animation, std::int32_t script);
    // Parent binding prepares the actual Animation before its VM update.
    void bind_animation(Animation* animation, std::int32_t script, Animation* parent);
    AnimationHandle spawn(const char* expected_stem, std::int32_t script,
                          const Vector3& position, float rotation,
                          std::int32_t layer, Animation** output);
    AnimationHandle spawn(const char* expected_stem,std::int32_t script,
                          std::int32_t layer,Animation** output);
    AnimationHandle spawn_flag8(const char* expected_stem,std::int32_t script,
                               const Vector3& position,float rotation,
                               std::int32_t layer,Animation** output);
    // Full native VM creation supports a null position and optional output.
    AnimationHandle spawn(const char* expected_stem,std::int32_t script,
                          const Vector3* position,float rotation,std::int32_t layer,
                          std::uint32_t flags,Animation** output);
};
#if defined(_M_IX86)
static_assert(sizeof(TextureRecord)==0x18);
static_assert(offsetof(TextureRecord,header)==0x10);
static_assert(offsetof(TextureRecord,flags)==0x14);
static_assert(sizeof(AnimationFile)==0x70);
static_assert(offsetof(AnimationFile,stage)==0x5c);
#endif
}
