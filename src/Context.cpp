#include "Context.hpp"
namespace th20 {
Context::Context() noexcept
    : primary_owner(nullptr), object_04(nullptr), enemies(nullptr), object_0c(nullptr),
      object_10(nullptr), object_14(nullptr), object_18(nullptr), object_1c(nullptr),
      object_20(nullptr), current_player(nullptr), object_28(nullptr), overlay_owner(nullptr) {}
EnemyController* Context::enemy_controller() { return enemies; }
}
