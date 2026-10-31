// Complete source-present TH20 157B file-existence Boss, NONEXACT.
// The original uses the real game lock slot 2, a copied native Win32
// filesystem::path, std::filesystem::exists and the destructor scopes.
// Current pinned MSVC20 emits 155B/46 vs native 157B/47, because old
// native path-copy construction also passes an observed format=0 word.
// Do not fabricate that legacy constructor or native E8 target in source.
#include "LockRegistry.hpp"
#include <filesystem>
#include <mutex>
namespace th20 {
bool game_file_exists_4107a0(const std::filesystem::path& source) {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(2));
    std::filesystem::path filename(source);
    return std::filesystem::exists(filename);
}
}
