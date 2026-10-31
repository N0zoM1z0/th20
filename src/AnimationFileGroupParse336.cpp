// Original 336B Renderer-owned AnimationFile ANM group parser.
// Source-present whole 336B/83 i386 compiler frontier, NONEXACT: two
// original stack-slot/frame bytes are not yet naturally reproduced.
// The outer 1022B game AnimationFile loader calls this method on the
// actual Renderer process global, passing its AnimationFile separately.
#include "NativeAnimationFileLoadView.hpp"
#include "GameResourceIo.hpp"
#include "AnimationFile.hpp"
#include "DiagnosticLog.hpp"
// The three diagnostic messages below are the original immutable CP932
// string objects; DiagnosticLog is the shared real game logger owner.
#include <cstdio>
#include <cstdint>
namespace th20 {
extern const char native_anm_err_corrupt_56e428[];
extern const char native_anm_err_version_56e464[];
extern const char native_anm_err_texture_56e488[];
std::int32_t NativeRendererAnmGroupView::parse_group_44ebf0(
    NativeAnimationFileLoadView* file, std::int32_t index,
    const NativeAnmGroupHeader* group) {
    std::int32_t length=0;
    if (group==nullptr) {
        report_log_error(&diagnostic_log,native_anm_err_corrupt_56e428);
        return -1;
    }
    const NativeAnmGroupHeader* record=group;
    if (record->signature!=8) {
        report_log_error(&diagnostic_log,native_anm_err_version_56e464);
        return -1;
    }
    if (record->flag_20==0) {
        const char* texture_path=reinterpret_cast<const char*>(record)
            +record->embedded_name_offset;
        if (texture_path[0]!='@') {
            char name[260];
            sprintf_s(name,"%s",texture_path);
            auto* bytes=read_game_resource(name,&length,1);
            if (!bytes) {
                report_log_error(&diagnostic_log,native_anm_err_texture_56e488,texture_path);
                return -1;
            }
            file->textures[index].external_size=static_cast<std::uint32_t>(length);
            file->textures[index].external_bytes=bytes;
        }
    }
    return 1;
}
}
