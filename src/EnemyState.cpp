#include "EnemyState.hpp"

namespace th20 {

EnemyAnimationLink::EnemyAnimationLink() : handle(), offset(), parent(-1) {}

// Default-initialize the shared_ptr. Value-initializing its defaulted native
// constructor adds an outer zeroing pass absent from the original value.
EnemyQueuedRecord::EnemyQueuedRecord() : parameters(), field_30(0),
    vector_34(), vector_40() {}

EnemyBounds::EnemyBounds() : x(0.0f), y(0.0f), width(0.0f), height(0.0f) {}

EnemyState::EnemyState() : identifier(), identifier_04(), entity(nullptr),
    animations(), field_1c(0), field_20(0), field_24(0), field_28(0), field_2c(0),
    field_30(0), field_34(0), field_38(0.0f), field_3c(0.0f), field_40(0.0f),
    field_44(0), field_48(0), field_4c(0.0f), field_50(0), field_54(0), field_58(0),
    bounds_5c(), bounds_64(), vector_6c(), counters(), timer_a8(), timer_b8(),
    motion_c8(), motion_110(), movements(), queued(), vector_170(), bounds_178(),
    identifier_188(), health(), pattern(), field_250(0), field_254(0),
    field_258(0), field_25c(0), field_260(0), field_264(0), field_268(0),
    field_26c(0), field_270(0), field_274(0.0f), field_278(10), field_27c(-1),
    field_280(0), field_284(0), timer_288(), timer_298(), timer_2a8(), phases(),
    flags{}, mesh(nullptr), field_2d8(0), field_2dc(0), field_2e0(0),
    field_2e4(0), field_2e8(0), context(nullptr) {}

EnemyState::~EnemyState() = default;

int EnemyState::initialize() {
    movements.clear();
    auto& movement_records = movements;
    movement_records.resize(1);
    field_268 = 20;
    field_26c = 3;
    field_264 = -1;
    field_254 = 0;
    field_254 = 0; // Both stores are present in the native initialization protocol.
    motion_110.clear();
    bounds_5c.x = 24.0f;
    bounds_5c.y = 24.0f;
    bounds_64.x = 24.0f;
    bounds_64.y = 24.0f;
    field_38 = 0.0f;
    field_270 = -1;
    pattern.reset();
    timer_a8 = 0;
    timer_b8 = 0;
    timer_288 = 0;
    timer_298 = 0;
    field_34 = 1;
    field_27c = -1;
    field_3c = 0.0f;
    field_40 = 0.0f;
    health.reset();
    phases.clear();
    auto& animation_records = animations;
    animation_records.resize(1);
    field_4c = 1.0f;
    field_284 = 0;
    return 0;
}

} // namespace th20
