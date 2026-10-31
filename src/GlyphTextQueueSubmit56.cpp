// Whole original 56B GDI glyph text submission bridge at 0x004162F0.
// The existing std::function is passed as a borrowed reference, not an
// owned 40-byte value. MSVC's real std::_Unfancy pointer forwarding is
// physically present in the original 56B method at native E8 +0x0D.
#include "NativeGlyphTextQueueView.hpp"
#include <memory>
#include <utility>
namespace th20 {
void NativeGlyphQueueView::submit_4162f0(std::function<void()>& task) {
    append_4131e0(child_04, std::move(*std::_Unfancy(&task)));
}
}
