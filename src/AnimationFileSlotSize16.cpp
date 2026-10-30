#include "AnimationFile.hpp"
#include <array>
namespace th20 {
void probe_file_slot_size(const std::array<AnimationFile*,42>& entries) {
    volatile std::size_t n=entries.size();
    (void)n;
}
}
