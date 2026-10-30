#include <cstdint>
namespace th20 {
struct NativeParticleSpawnFileView {
    void spawn_core_450cb0(void* output,std::uint32_t script,
        std::uint32_t variant,std::uint32_t behavior,float factor,
        std::int32_t depth,std::int32_t flag,std::int32_t unused);
    void* spawn_45d210(void* output,std::uint32_t script,
        std::uint32_t variant,std::uint32_t behavior,float factor,
        std::int32_t special);
};
void* NativeParticleSpawnFileView::spawn_45d210(void* output,
    std::uint32_t script,std::uint32_t variant,
    std::uint32_t behavior,float factor,std::int32_t special) {
    std::int32_t flag;
    if (special == 1) flag=16;
    else flag=0;
    spawn_core_450cb0(output,script,variant,behavior,factor,-1,flag,0);
    return output;
}
}
