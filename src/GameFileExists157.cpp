// Original complete 157B game filesystem existence query. The caller passes
// a narrow const char* by value; the native path(char const*) constructor
// takes its address and the default auto_format = 0. The copied-path theory
// was wrong: all seven native E8 targets are existing real STL/game heads.
#include "LockRegistry.hpp"
#include <filesystem>
#include <mutex>
namespace th20 {
bool game_file_exists_4107a0(const char* source) {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(2));
    std::filesystem::path filename(source);
    return std::filesystem::exists(filename);
}
}
