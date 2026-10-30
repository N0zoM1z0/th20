#include "AnimationFile.hpp"
#include "Animation.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "DiagnosticAllocator.hpp"
#include <cstdint>
namespace th20 {
struct NativeFileClearPoolView : AnimationPoolOwner {
    void detach_file_44fd30(AnimationFile* file, char flag);
    void cleanup_texture_44c510(TextureRecord* record);
};
void AnimationFile::clear() {
    if (bytes != nullptr) {
        reinterpret_cast<NativeFileClearPoolView*>(current_animation_pool)->detach_file_44fd30(this,0);
        for (std::int32_t index=0;index<texture_count;++index) {
            reinterpret_cast<NativeFileClearPoolView*>(current_animation_pool)->cleanup_texture_44c510(&textures[index]);
        }
        process_allocator->release_array(reinterpret_cast<std::uint8_t*>(textures));
        textures=nullptr;
        process_allocator->release_array(reinterpret_cast<std::uint8_t*>(sprites));
        sprites=nullptr;
        process_allocator->release_array(reinterpret_cast<std::uint8_t*>(scripts));
        scripts=nullptr;
        if (field_6c!=0) {
            process_allocator->release_bytes(reinterpret_cast<void*>(field_6c));
            field_6c=0;
        }
        if (bytes!=nullptr) {
            process_allocator->release_bytes(bytes);
            bytes=nullptr;
        }
        process_allocator->release_array(templates);
        templates=nullptr;
    }
}
}
