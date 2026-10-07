#include "EnemyController.hpp"
#include "Context.hpp"
namespace th20 {

std::int32_t* Enemy::integer_destination(std::int32_t index) {
    switch (index) {
    case -9985: return reinterpret_cast<std::int32_t*>(&state.counters.field_00);
    case -9984: return reinterpret_cast<std::int32_t*>(&state.counters.field_04);
    case -9983: return reinterpret_cast<std::int32_t*>(&state.counters.field_08);
    case -9982: return reinterpret_cast<std::int32_t*>(&state.counters.field_0c);
    case -9949: return reinterpret_cast<std::int32_t*>(&context->enemy_controller()->data.field_38);
    case -9948: return reinterpret_cast<std::int32_t*>(&context->enemy_controller()->data.field_3c);
    case -9947: return reinterpret_cast<std::int32_t*>(&context->enemy_controller()->data.field_40);
    case -9943: return context->enemy_controller()->selected(0) ? reinterpret_cast<std::int32_t*>(&context->enemy_controller()->selected(0)->state.counters.field_00) : reinterpret_cast<std::int32_t*>(&state.counters.field_00);
    case -9942: return context->enemy_controller()->selected(0) ? reinterpret_cast<std::int32_t*>(&context->enemy_controller()->selected(0)->state.counters.field_04) : reinterpret_cast<std::int32_t*>(&state.counters.field_04);
    case -9941: return context->enemy_controller()->selected(0) ? reinterpret_cast<std::int32_t*>(&context->enemy_controller()->selected(0)->state.counters.field_08) : reinterpret_cast<std::int32_t*>(&state.counters.field_08);
    case -9940: return context->enemy_controller()->selected(0) ? reinterpret_cast<std::int32_t*>(&context->enemy_controller()->selected(0)->state.counters.field_0c) : reinterpret_cast<std::int32_t*>(&state.counters.field_0c);
    case -9926: return reinterpret_cast<std::int32_t*>(&context->enemy_controller()->data.counters.field_00);
    case -9925: return reinterpret_cast<std::int32_t*>(&context->enemy_controller()->data.counters.field_04);
    case -9924: return reinterpret_cast<std::int32_t*>(&context->enemy_controller()->data.counters.field_08);
    case -9923: return reinterpret_cast<std::int32_t*>(&context->enemy_controller()->data.counters.field_0c);
    case -9895: return &enemy_script_globals[0];
    case -9894: return &enemy_script_globals[1];
    case -9893: return &enemy_script_globals[2];
    case -9892: return &enemy_script_globals[3];
    default: return nullptr;
    }
}

float* Enemy::float_destination(std::int32_t index) {
    switch (index) {
    case -9981: return &state.counters.field_10;
    case -9980: return &state.counters.field_14;
    case -9979: return &state.counters.field_18;
    case -9978: return &state.counters.field_1c;
    case -9935: return &state.counters.field_20;
    case -9934: return &state.counters.field_24;
    case -9933: return &state.counters.field_28;
    case -9932: return &state.counters.field_2c;
    case -9939: return context->enemy_controller()->selected(0) ? &context->enemy_controller()->selected(0)->state.counters.field_10 : &state.counters.field_10;
    case -9938: return context->enemy_controller()->selected(0) ? &context->enemy_controller()->selected(0)->state.counters.field_14 : &state.counters.field_14;
    case -9937: return context->enemy_controller()->selected(0) ? &context->enemy_controller()->selected(0)->state.counters.field_18 : &state.counters.field_18;
    case -9936: return context->enemy_controller()->selected(0) ? &context->enemy_controller()->selected(0)->state.counters.field_1c : &state.counters.field_1c;
    case -9922: return &context->enemy_controller()->data.counters.field_10;
    case -9921: return &context->enemy_controller()->data.counters.field_14;
    case -9920: return &context->enemy_controller()->data.counters.field_18;
    case -9919: return &context->enemy_controller()->data.counters.field_1c;
    case -9918: return &context->enemy_controller()->data.counters.field_20;
    case -9917: return &context->enemy_controller()->data.counters.field_24;
    case -9916: return &context->enemy_controller()->data.counters.field_28;
    case -9915: return &context->enemy_controller()->data.counters.field_2c;
    case -9995: return &state.movements[0].motion.position_ref().x;
    case -9994: return &state.movements[0].motion.position_ref().y;
    case -9993: return &state.movements[1].motion.position_ref().x;
    case -9992: return &state.movements[1].motion.position_ref().y;
    default: return nullptr;
    }
}

Enemy* EnemyController::selected(std::uint32_t index) { return data.handles.at(index).resolve(); }

Enemy* EnemyHandle::resolve() {
    Enemy* result = nullptr;
    if (enemy_controller(0)) {
        auto* controller = enemy_controller(0);
        auto identifier = value;
        result = controller->find(identifier);
    }
    return result;
}

} // namespace th20
