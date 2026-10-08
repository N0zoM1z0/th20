#pragma once

#include "ProgressStorage.hpp"
#include "Worker.hpp"

namespace th20 {

// Actual owner of current/backup records, their buffers and the file Worker.
// The meaning and element widths of the zeroed 64-byte interval remain open.
struct ProgressSaveManager {
    ProgressSnapshot current, backup;
    std::uint32_t field_124280=0;
    std::uint8_t field_124284[64]{};
    Worker worker;

    ProgressSaveManager();
    ~ProgressSaveManager();
    std::int32_t commit();
    std::int32_t copy_current_to_backup();
    std::int32_t merge_current();

    void load(void* argument);
    void save(void* argument);
    std::int32_t write(const char* filename, ProgressSnapshot* snapshot);
    std::int32_t parse(ProgressSnapshot* snapshot);
};

// The member-task specialization belongs to the Worker TU and its own profile.
extern template void Worker::start<ProgressSaveManager,
    void (ProgressSaveManager::*)(void*), void*>(
    ProgressSaveManager*, void (ProgressSaveManager::*)(void*), void*&);

#if defined(_M_IX86)
static_assert(offsetof(ProgressSaveManager, backup)==0x92140);
static_assert(offsetof(ProgressSaveManager, field_124280)==0x124280);
static_assert(offsetof(ProgressSaveManager, field_124284)==0x124284);
static_assert(offsetof(ProgressSaveManager, worker)==0x1242c4);
static_assert(sizeof(ProgressSaveManager)==0x1242d8);
static_assert(sizeof(void (ProgressSaveManager::*)(void*))==4);
static_assert(sizeof(Worker::MemberTask<ProgressSaveManager,
    void (ProgressSaveManager::*)(void*), void*>)==12);
#endif

} // namespace th20
