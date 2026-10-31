#pragma once
#include <cstdint>
namespace th20 {
// Non-owning native views: the full Card UI and persistent record store
// layouts remain unresolved, so do not model these as prefix-padded owners.
struct NativeCardUiDirtyView {
    void mark_finished_4883a0();
};
struct NativeSpellRecordView {
    void increment_capture_488510(std::int32_t kind);
};
struct NativeCardRecordArchive {
    std::uint8_t* secondary_488700();
};
struct NativeSpellRecordArrayView {
    NativeSpellRecordView* record_486e10(std::int32_t index);
};
}
