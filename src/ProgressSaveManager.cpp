#include "ProgressSaveManager.hpp"
#include "DiagnosticAllocator.hpp"
#include <cstring>

namespace th20 {

ProgressSaveManager::ProgressSaveManager() {
    worker.close_and_join();
    auto& owned_worker=worker;
    void* argument=nullptr;
    owned_worker.start(this, &ProgressSaveManager::load, argument);
}

std::int32_t ProgressSaveManager::commit() {
    worker.close_and_join();
    auto& owned_worker=worker;
    void* argument=nullptr;
    owned_worker.start(this, &ProgressSaveManager::save, argument);
    return 0;
}

ProgressSaveManager::~ProgressSaveManager() {
    commit();
    worker.close_and_join();
    if (current.file_buffer) TH20_RELEASE_BYTES_AND_RESET(current.file_buffer);
    if (current.decoded_buffer) TH20_RELEASE_BYTES_AND_RESET(current.decoded_buffer);
    if (backup.file_buffer) TH20_RELEASE_BYTES_AND_RESET(backup.file_buffer);
    if (backup.decoded_buffer) TH20_RELEASE_BYTES_AND_RESET(backup.decoded_buffer);
}

std::int32_t ProgressSaveManager::copy_current_to_backup() {
    // The native block includes all eighteen selectable profiles and fallback.
    // Buffer ownership and file size are deliberately outside both copies.
    std::memcpy(backup.profiles, current.profiles,
        sizeof(current.profiles)+sizeof(current.fallback));
    std::memcpy(&backup.metadata, &current.metadata, sizeof(current.metadata));
    return 0;
}

std::int32_t ProgressSaveManager::merge_current() {
    auto* destination=&current;
    std::memcpy(destination->profiles, backup.profiles,
        sizeof(backup.profiles)+sizeof(backup.fallback));
    std::memcpy(&destination->metadata, &backup.metadata, sizeof(backup.metadata));
    std::int32_t result=parse(destination);
    copy_current_to_backup();
    return result;
}

} // namespace th20
