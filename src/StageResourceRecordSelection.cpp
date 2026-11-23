#include "StageResource.hpp"

namespace th20 {

// Native 0x004773C0 walks the variable-length records at owner+0x3330.
// The original type/name is unknown; only this 12-byte record prefix and the
// Background Timer/selected-offset members are established by the native body.
void StageResourceOwner::select_record(std::int32_t identifier) {
    const auto* current =
        reinterpret_cast<const StageResourceRecordHeader*>(record_data);
    while (current->timer_value >= 0) {
        if (current->kind == 0x10 && current->identifier[0] == identifier) {
            background.selected_record_offset = static_cast<std::uint32_t>(
                reinterpret_cast<const std::byte*>(current) - record_data);
            background.selection_timer = *reinterpret_cast<const std::int32_t*>(
                record_data + background.selected_record_offset);
            break;
        }
        current = reinterpret_cast<const StageResourceRecordHeader*>(
            reinterpret_cast<const std::byte*>(current) + current->stride);
    }
}

} // namespace th20
