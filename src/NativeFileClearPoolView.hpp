#pragma once
// Provisional non-owning original Renderer/File teardown ABI. The actual
// 284B AnimationFile::clear and 94B texture cleanup share these declarations.
#include "AnimationFile.hpp"
#include "AnimationRuntimeOwner.hpp"
namespace th20 {
struct NativeFileClearPoolView : AnimationPoolOwner {
    void detach_file_44fd30(AnimationFile* file,char flag);
    void cleanup_texture_44c510(TextureRecord* record);
};
}
