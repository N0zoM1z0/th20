// Four original whole Card spell-finish leaves. The two pointer/array helpers
// have unresolved compiler-or-game ownership and no duplicate authored credit.
#include "NativeCardSpellViews.hpp"
namespace th20 {
void NativeCardUiDirtyView::mark_finished_4883a0() {
    *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x3344) |= 1u;
}
void NativeSpellRecordView::increment_capture_488510(std::int32_t kind) {
    if (reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0xC0)[kind] < 99999)
        ++reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0xC0)[kind];
}
std::uint8_t* NativeCardRecordArchive::secondary_488700() {
    return reinterpret_cast<std::uint8_t*>(this)+0x8A460;
}
NativeSpellRecordView* NativeSpellRecordArrayView::record_486e10(std::int32_t index) {
    return reinterpret_cast<NativeSpellRecordView*>(reinterpret_cast<std::uint8_t*>(this)+index*0xE0);
}
}
