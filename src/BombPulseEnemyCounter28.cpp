// Native 0x00477F40 EnemyController+0x4C, a real EnemyData field_3C.
#include "NativeBombPulseViews.hpp"
#include "EnemyController.hpp"
namespace th20 {
void NativeBombEnemyCounterView::advance_477f40(std::int32_t delta) {
    reinterpret_cast<EnemyController*>(this)->data.field_3c += delta;
}
}
