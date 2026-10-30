// Native original 83B/30-i386 AnimationFile spawn wrapper.
// Real C++ return-by-value AnimationHandle and the full native 922B callee;
// the compiler owns the hidden return-object pointer, not a fake explicit
// void* output argument. Full scoped strict proof in CORE/RECON-957/958.
#include "AnimationFile.hpp"
#include <cstdint>
namespace th20 {
struct NativeParticleSpawnFileView : AnimationFile {
    AnimationHandle spawn_45d210(const char* expected_stem,
        std::int32_t script, const Vector3* position, float rotation,
        std::int32_t special);
};
AnimationHandle NativeParticleSpawnFileView::spawn_45d210(
    const char* expected_stem,std::int32_t script,const Vector3* position,
    float rotation,std::int32_t special) {
    std::int32_t flag;
    if (special == 1) flag=16;
    else flag=0;
    return AnimationFile::spawn(expected_stem,script,position,rotation,-1,flag,nullptr);
}
}
