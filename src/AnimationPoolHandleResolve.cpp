// Complete original native 456-byte SprtCtrlInf::getSprt(SprtID) behavior,
// retained under the existing ABI-compatible AnimationPoolOwner::resolve_handle
// name because its many already native-exact callers supply a four-byte word.
// The source uses SprtID lvalue views only at true native member-operation
// boundaries; do not add an artificial adapter or change the public ABI.
// Two original list predicates and normal pool lookups share this one body.
#include "AnimationRuntimeOwner.hpp"
#include "Animation.hpp"
#include "AnimationHandle.hpp"
#include "SprtID.hpp"
#include <array>
#include <functional>
#include <cstdint>
#include <cstddef>

namespace th20 {
namespace {
using LinkPredicate = std::function<bool(IntrusiveLink<Animation>&)>;
// Only the +0/+0x18 lists and 0x48 slot stride are observed here. The
// trailing third list-shaped slot remains a layout hypothesis rather than
// a claim about its native use or original source-level type name.
struct AnimationLookupList : IntrusiveList<Animation> {
    IntrusiveLink<Animation>* find_if(LinkPredicate predicate);
};
struct AnimationLookupGroup {
    AnimationLookupList first;
    AnimationLookupList second;
    AnimationLookupList unreviewed_third;
};
#if defined(_M_IX86)
static_assert(sizeof(AnimationLookupList) == 0x18);
static_assert(sizeof(AnimationLookupGroup) == 0x48);
static_assert(sizeof(PooledAnimation) == 0x600);
static_assert(offsetof(PooledAnimation, active) == 0x5f8);
static_assert(offsetof(Animation, handle) == 0x4c0);
#endif
}

static IntrusiveLink<Animation>* __fastcall find_link_with_predicate(
    IntrusiveLink<Animation>* first, LinkPredicate predicate) {
    IntrusiveLink<Animation>* current = first;
    while (current != nullptr) {
        if (predicate(*current)) return current;
        current = current->next_value();
    }
    return nullptr;
}

// The native 159-byte ECX/40-byte-by-value predicate loop is a separate
// original game method from the 154-byte list entry wrapper. Both operate on
// the real intrusive link representation, without a fabricated owner object.
IntrusiveLink<Animation>* AnimationLookupList::find_if(LinkPredicate predicate) {
    IntrusiveLink<Animation>* result;
    if (next_value()) {
        IntrusiveLink<Animation>* first = next_value();
        result = find_link_with_predicate(first, predicate);
    } else {
        result = nullptr;
    }
    return result;
}

Animation* AnimationPoolOwner::resolve_handle(std::uint32_t raw_id) {
    // The immutable original argument is a 4-byte SprtID, while previously
    // accepted callers use the compatible 4-byte uint32_t ABI. Each direct
    // type view refers to the existing by-value stack argument (not a copy).
    // No pointer, ownership or game state is changed by this local view.
    IntrusiveLink<Animation>* selected;
    if (reinterpret_cast<SprtID&>(raw_id) == 0) return nullptr;
    if ((reinterpret_cast<SprtID&>(raw_id) & 0xffffu) == 0xffffu) {
        // Special IDs (low word FFFF) search the two observed live-link
        // lists. The original uses two distinct four-byte value-capturing lambdas
        // and passes each as a 40-byte std::function object by value.
        for (std::int32_t index = 0; index < 1; ++index) {
            auto& groups = *reinterpret_cast<std::array<AnimationLookupGroup, 1>*>(
                reinterpret_cast<unsigned char*>(this) + 0x6c8);
            if ((selected = groups[index].first.find_if([raw_id](IntrusiveLink<Animation>& node) {
                return reinterpret_cast<const SprtID&>(node.node_value()->handle) ==
                       reinterpret_cast<const SprtID&>(raw_id);
            }))) return selected->node_value();
            auto& second_groups = *reinterpret_cast<std::array<AnimationLookupGroup, 1>*>(
                reinterpret_cast<unsigned char*>(this) + 0x6c8);
            if ((selected = second_groups[index].second.find_if([raw_id](IntrusiveLink<Animation>& node) {
                return reinterpret_cast<const SprtID&>(node.node_value()->handle) ==
                       reinterpret_cast<const SprtID&>(raw_id);
            }))) return selected->node_value();
        }
        reinterpret_cast<SprtID&>(raw_id) = 0;
    } else {
        // Normal IDs index real 0x600-byte pooled records at owner+0x710.
        // Active lives at record+0x5f8, with the handle word at +0x4c0.
        const std::uint32_t record_index = reinterpret_cast<SprtID&>(raw_id) & 0xffffu;
        auto& records_a = *reinterpret_cast<std::array<PooledAnimation, 65536>*>(
            reinterpret_cast<unsigned char*>(this) + 0x710);
        if (!records_a[record_index].active) {
            reinterpret_cast<SprtID&>(raw_id) = 0;
            return nullptr;
        }
        auto& records_b = *reinterpret_cast<std::array<PooledAnimation, 65536>*>(
            reinterpret_cast<unsigned char*>(this) + 0x710);
        if (reinterpret_cast<const SprtID&>(records_b[record_index].animation.handle) !=
            reinterpret_cast<SprtID&>(raw_id)) {
            reinterpret_cast<SprtID&>(raw_id) = 0;
            return nullptr;
        }
        auto& records_c = *reinterpret_cast<std::array<PooledAnimation, 65536>*>(
            reinterpret_cast<unsigned char*>(this) + 0x710);
        return &records_c[record_index].animation;
    }
    return nullptr;
}
} // namespace th20
