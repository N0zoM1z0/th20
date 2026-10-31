// Whole original 1022B AnimationFile resource loader: native STRICT EXACT.
// Complete original 219 i386, 23 genuine E8 and 12 real PE HIGHLOW roles.
// The true Renderer-side per-group parser has distinct original 336B code.
// No guessed wchar_t[130]: the original has a 260B narrow character path
// and literal original .rdata "%s" (0x0056E0E4), via sprintf_s<260>.
#include "NativeAnimationFileLoadView.hpp"
#include "GameResourceIo.hpp"
#include "Animation.hpp"
#include "DiagnosticObjectFactories.hpp"
#include <filesystem>
#include <cstdio>
#include <string>
#include <cstdint>
namespace th20 {
std::int32_t NativeAnimationFileLoadView::load_resource_44a700(const char* requested) {
    char file_path[260];
    sprintf_s(file_path,"%s",requested);
    std::uint8_t* raw=read_game_resource(file_path,nullptr,0);
    if (raw==nullptr) return -1;

    // The original initializes all four independent counters immediately
    // after the resource succeeds, before the path conversion EH scopes.
    std::uint32_t group_count=0;
    std::uint32_t scripts_total=0;
    std::uint32_t sprites_total=0;
    std::int32_t index=0;
    // Actual native owner stores this buffer at AnimationFile+0x3C.
    bytes=raw;
    std::filesystem::path disk_path(requested);
    filename=disk_path.filename().string<char>(std::allocator<char>{});
    stem=disk_path.stem().string<char>(std::allocator<char>{});

    const NativeAnmGroupHeader* group=
        reinterpret_cast<const NativeAnmGroupHeader*>(raw);
    for (;;) {
        ++group_count;
        scripts_total+=group->script_count;
        sprites_total+=group->sprite_count;
        if (group->next_header_offset==0) break;
        group=reinterpret_cast<const NativeAnmGroupHeader*>(
            reinterpret_cast<const std::uint8_t*>(group)+group->next_header_offset);
    }
    texture_count=static_cast<std::int32_t>(group_count);
    textures=process_allocator->allocate_array<TextureRecord>(
        "D:\\cygwin\\home\\zun\\prog\\th20\\src\\core\\sprtlib.cpp:905 SprtGroupTexInf",
        static_cast<std::int32_t>(group_count));
    sprites=process_allocator->allocate_array<SpriteData>(
        "D:\\cygwin\\home\\zun\\prog\\th20\\src\\core\\sprtlib.cpp:906 SprtDataInf",
        static_cast<std::int32_t>(sprites_total));
    scripts=process_allocator->allocate_array<AnmInstruction*>(
        "D:\\cygwin\\home\\zun\\prog\\th20\\src\\core\\sprtlib.cpp:907 int*",
        static_cast<std::int32_t>(scripts_total));
    script_count=scripts_total;
    sprite_count=sprites_total;

    group=reinterpret_cast<const NativeAnmGroupHeader*>(raw);
    for (;;) {
        // The original returns success even when one group decoder fails;
        // the complete generated original has a distinct early-return
        // destructor path BEFORE the successful-final-group tail.
        const std::int32_t result=
            reinterpret_cast<NativeRendererAnmGroupView*>(current_animation_pool)
                ->parse_group_44ebf0(this,index,group);
        if (result<0) return 0;
        ++index;
        if (group->next_header_offset==0) break;
        group=reinterpret_cast<const NativeAnmGroupHeader*>(
            reinterpret_cast<const std::uint8_t*>(group)+group->next_header_offset);
    }
    // Original final-group fallthrough allocates templates AFTER the loop.
    // The unsuccessful per-group result has its own earlier return and
    // path destructor; the two native EH exits must not be combined.
    templates=process_allocator->allocate_array<Animation>(
        "D:\\cygwin\\home\\zun\\prog\\th20\\src\\core\\sprtlib.cpp:929 SprtInf",
        static_cast<std::int32_t>(scripts_total));
    return 0;
}
}
