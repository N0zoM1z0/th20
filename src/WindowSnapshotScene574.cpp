// Real 574B WindowState scene/snapshot updater at original 0x00419760.
// This is full typed game source (input, filesystem, graphics capture).
// Original whole-native exactness remains OPEN; never count 574 game bytes
// until the full PE/COFF source relocations and ordinary bytes match.
#include "NativeWindowFrameScheduleView.hpp"
#include "InputState.hpp"
#include "GameFileIo.hpp"
#include <filesystem>
#include <string>
#include <cstdio>
#include <cstdint>
namespace th20 {
bool game_file_exists_4107a0(const char* filename);
struct NativeWindowCaptureRenderer {
    void prepare_frame_41bfc0();
};
extern NativeWindowCaptureRenderer* native_window_capture_renderer_5c0028;
extern InputButtonState* native_snapshot_input_bindings_5b889c[];
extern std::uint32_t native_snapshot_options_5b87e8;
extern const char native_snapshot_subdir_56caac[9];
extern const char native_snapshot_pattern_56cabc[14];
struct NativeWindowCaptureGraphics {
    void write_snapshot_4de040(const char* path);
};
extern NativeWindowCaptureGraphics native_window_capture_graphics_5c4d40;
int __cdecl native_snapshot_format_41f220(char* out, std::size_t capacity,
                                           const char* pattern, std::int32_t number);

void NativeWindowFrameScheduleView::update_scene_419760() {
    native_window_capture_renderer_5c0028->prepare_frame_41bfc0();
    // The original x86 shifts index 4 left once as a BYTE offset (+8),
    // selecting the third four-byte input pointer, not array entry 8.
    std::uint32_t snapshot_trigger=0;
    if (native_snapshot_input_bindings_5b889c[2])
        snapshot_trigger=native_snapshot_input_bindings_5b889c[2]->pressed_bits(0x40000);
    else snapshot_trigger=0;
    if (snapshot_trigger && (native_snapshot_options_5b87e8 & 0x40u)==0) {
        std::filesystem::path target(window_state.user_data_directory);
        target/=native_snapshot_subdir_56caac;
        std::filesystem::create_directories(target);
        char filename[256];
        std::int32_t index=0;
        for (;index<10000;++index) {
            native_snapshot_format_41f220(filename,sizeof filename,
                    native_snapshot_pattern_56cabc,index);
            target=window_state.user_data_directory;
            target/=native_snapshot_subdir_56caac;
            target/=filename;
            const std::string expanded=target.string();
            if (!game_file_exists_4107a0(expanded.c_str())) break;
        }
        if (index<10000) {
            const std::string expanded=target.string();
            native_window_capture_graphics_5c4d40.write_snapshot_4de040(expanded.c_str());
        }
    }
}
}
