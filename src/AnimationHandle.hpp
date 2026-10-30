#pragma once

#include <cstddef>
#include <cstdint>

namespace th20 {

class Animation;
struct Vector3;

// REF-017: four-byte values constructed in Notice's seven-element array and
// secondary member. Native resolve clears a value when its lookup fails.
struct AnimationHandle {
    std::uint32_t value;

    AnimationHandle() noexcept;
    // Native word assignment; the shared physical head is audited separately.
    void operator=(std::uint32_t input);
    Animation* resolve();
    // Native alternate 56B resolver: non-null result or resident pool Animation.
    Animation* resolve_or_resident_44cf10();
    // Native 39B wrapper publishes a callback to resolved/resident Animation.
    void set_entry_callback_forward_44f100(std::int32_t (*callback)(Animation*));
    // Original whole 45-byte native live-handle validity predicate.
    bool is_valid();
    // Original whole 26-byte positional member forwarding wrapper.
    void set_position_forward(const Vector3& position);
    Animation* find_child(std::int32_t identifier, std::int32_t ordinal);
    void interrupt(std::int32_t event);
    // Genuine distinct original 35B bridge to the 261B child-event/VM pass.
    void update_descendants_event_44f0d0(std::int32_t event);
    void interrupt_offset_7(std::int32_t event);
    void retire();
    bool operator!=(std::uint32_t input) const;
    // Native Player caller observes genuine word equality. The complete
    // 45-byte body is byte-identical to the independently accepted
    // EffectAnimationHandle equality (possible original COMDAT folding);
    // no second physical original body is credited.
    bool operator==(std::uint32_t input) const;
    void set_position(const Vector3& position);
};

static_assert(sizeof(AnimationHandle) == 4);
static_assert(offsetof(AnimationHandle, value) == 0);

} // namespace th20
