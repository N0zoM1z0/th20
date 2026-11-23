#include "StoneEnemyRecord.hpp"
#include "WeaponStoneInfo.hpp"
#include "DiagnosticObjectFactories.hpp"

namespace th20 {

StoneEnemyRecord::StoneEnemyRecord()
    : link(), enemy_14(), handle_18(), timer_1c() {
    // The original constructor first default-constructs the five-pointer link,
    // then publishes this record as its node. Keep the separate initialize call.
    link.initialize(this);
}

// The native source diagnostic string is the exact original __FILE__/line/type
// label passed to DiagnosticAllocator::allocate_object from game/stoneenemy.cpp.
const char stone_enemy_record_diagnostic_label[] =
    "D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\stoneenemy.cpp:76 StoneEnemyInf";

template StoneEnemyRecord* DiagnosticAllocator::allocate_object<StoneEnemyRecord>(const char*);

// Native 0x00512F60: allocate the record, append its intrusive link, then run
// the large record/UI initializer. Its 1,847-byte body is still source-open.
void StoneEnemyController::add_record(std::int32_t enemy_handle,
                                      std::int32_t player_index) {
    auto* const record = process_allocator->allocate_object<StoneEnemyRecord>(
        stone_enemy_record_diagnostic_label);
    records.append(&record->link);
    record->initialize(enemy_handle, player_index);
}

} // namespace th20
