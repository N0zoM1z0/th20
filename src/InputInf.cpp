// Whole original 26-byte InputInf per-Player input source lookup.
// This RTTI-attested original class owns the live pointer table; no
// pointer-alias casts or fake 0x2E30-byte padding are needed.
#include "InputInf.hpp"

namespace th20 {
InputButtonState* InputInf::for_view(std::int32_t logical_index) {
    return active_buttons[logical_index];
}
} // namespace th20
