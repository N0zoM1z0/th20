// Full, typed semantic implementation of original 0x0044CD00, 456-byte
// Animation pool handle lookup. Still NONEXACT; never count the native parent
// until the entire compiled body and real call/relocation graph pass replay.
// Native RTTI independently names SprtCtrlInf::getSprt(SprtID) and two
// LinkInf<SprtInf*> predicate closures; current public owner/handle aliases
// retain the ABI of already exact C++ callers.
#include "AnimationRuntimeOwner.hpp"
#include "Animation.hpp"
#include "AnimationHandle.hpp"
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

IntrusiveLink<Animation>* AnimationLookupList::find_if(LinkPredicate predicate) {
    for (IntrusiveLink<Animation>* link = this->next_value();
         link != nullptr; link = link->next_value()) {
        if (predicate(*link)) return link;
    }
    return nullptr;
}

Animation* AnimationPoolOwner::resolve_handle(std::uint32_t id) {
    // A zero ID has no owner. The locked original stores its four-byte
    // by-value identifier at [ebp+8]; a rejected ID is not cleared in the
    // caller, only in the original callee's local copy.
    if (id == 0) return nullptr;
    if ((id & 0xffffu) == 0xffffu) {
        // Special IDs (low word FFFF) search the two observed live-link
        // lists. The original uses two distinct reference-capturing lambdas
        // and passes each as a 40-byte std::function object by value.
        auto& groups = *reinterpret_cast<std::array<AnimationLookupGroup, 1>*>(
            reinterpret_cast<unsigned char*>(this) + 0x6c8);
        for (std::int32_t index = 0; index < 1; ++index) {
            auto& entry = groups[index];
            if (auto* link = entry.first.find_if([&id](IntrusiveLink<Animation>& node) {
                return node.node_value()->handle.value == id;
            })) return link->node_value();
            if (auto* link = entry.second.find_if([&id](IntrusiveLink<Animation>& node) {
                return node.node_value()->handle.value == id;
            })) return link->node_value();
        }
        id = 0;
        return nullptr;
    }
    // Normal IDs index real 0x600-byte pooled records at owner+0x710.
    // Active lives at record+0x5f8, with the handle word at +0x4c0.
    auto& records = *reinterpret_cast<std::array<PooledAnimation, 65536>*>(
        reinterpret_cast<unsigned char*>(this) + 0x710);
    const std::uint32_t record_index = id & 0xffffu;
    if (!records[record_index].active) { id = 0; return nullptr; }
    if (records[record_index].animation.handle.value != id) { id = 0; return nullptr; }
    return &records[record_index].animation;
}
} // namespace th20
