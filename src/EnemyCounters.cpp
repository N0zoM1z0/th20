#include "EnemyCounters.hpp"

namespace th20 {

EnemyCounters::EnemyCounters() {
    field_00 = 0;
    field_04 = 0;
    field_08 = 0;
    field_0c = 0;
    field_10 = 0.0f;
    field_14 = 0.0f;
    field_18 = 0.0f;
    field_1c = 0.0f;
    field_20 = 0.0f;
    field_24 = 0.0f;
    field_28 = 0.0f;
    field_2c = 0.0f;
}

void EnemyCounters::reset() {
    field_0c = 0;
    field_08 = 0;
    field_04 = 0;
    field_00 = 0;
    field_2c = 0.0f;
    field_28 = 0.0f;
    field_24 = 0.0f;
    field_20 = 0.0f;
    field_1c = 0.0f;
    field_18 = 0.0f;
    field_14 = 0.0f;
    field_10 = 0.0f;
}

} // namespace th20
