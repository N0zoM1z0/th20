#pragma once
#include <cstdint>

namespace th20 {
// Native process handle at 5AE060; its startup definition remains pending.
extern void* game_file_handle;
std::int32_t open_game_output(const char* filename);
std::int32_t write_game_output(const void* bytes, std::uint32_t size);
std::int32_t close_game_output();
} // namespace th20
