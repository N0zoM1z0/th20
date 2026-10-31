#pragma once
#include <cstdint>
namespace th20 {
// Non-owning view on real Card+0x78 flag word, no invented Card suffix.
struct NativeCardStartFlagsView {
    void clear_capture_effect_flag_4888c0();
    void set_spell_flag9_488960(std::uint32_t bit);
};
}
