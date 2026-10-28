// Complete native 305B ensure-only and 396B writable COW selectors.
// Real original EnemyState PMR forward_list and shared EtamaArgInf owner;
// the record+metadata pointer pair is the actual native ABI.
#include "EnemyState.hpp"
#include "DebugAllocator.hpp"
#include <iterator>
#include <memory>
namespace th20 {
std::pair<EnemyQueuedRecord*,ShotMetadata*> EnemyState::shared_shot(std::uint32_t index) {
    DebugAllocator<ShotMetadata> allocator;
    if (std::distance(queued.begin(), queued.end()) < index + 1)
        queued.resize(index + 1);
    auto iterator = queued.begin();
    std::advance(iterator, index);
    auto* record = &*iterator;
    if (record->owner == nullptr)
        record->owner = std::allocate_shared<ShotMetadata>(allocator);
    auto* metadata = record->owner.get();
    return {record,metadata};
}
std::pair<EnemyQueuedRecord*,ShotMetadata*> EnemyState::writable_shot(std::uint32_t index) {
    DebugAllocator<ShotMetadata> allocator;
    if (std::distance(queued.begin(), queued.end()) < index + 1)
        queued.resize(index + 1);
    auto iterator = queued.begin();
    std::advance(iterator, index);
    auto* record = &*iterator;
    if (record->owner == nullptr || record->owner.use_count() > 1) {
        if (record->owner != nullptr)
            record->owner = std::allocate_shared<ShotMetadata>(allocator, *record->owner);
        else
            record->owner = std::allocate_shared<ShotMetadata>(allocator);
    }
    auto* metadata = record->owner.get();
    return {record,metadata};
}
}
