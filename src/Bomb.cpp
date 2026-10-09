#include "Bomb.hpp"
#include "EclDiagnostic.hpp"
#include "FunctionChainController.hpp"

namespace th20 {
Bomb::Bomb():field_04(0),field_78(0),field_7c(0),view_index(0),context(nullptr) {}
Bomb::~Bomb() {
    handle_70.retire();handle_74.retire();
    bomb_controller(0)->active_bomb=nullptr;
    bomb_controller(0)->active_state=0;
}
void Bomb::select_context(std::int32_t index) {
    view_index=index;context=&session.context(view_index);
}
std::int32_t Bomb::update() {return 0;}
std::int32_t Bomb::draw() {return 0;}
std::int32_t Bomb::finish() {return 0;}
std::int32_t Bomb::event(const Vector3*,const Vector2*) {return 0;}
BombController::BombController() noexcept
    :field_10(0),active_bomb(nullptr),active_state(0),field_2c(0),field_30(0),
     view_index(0),context(nullptr) {
    ecl_diagnostic_hint("initialize BombInf \n");
}
BombController::~BombController() {
    ecl_diagnostic_hint("shutdown BombInf \n");
    process_allocator->release_object(active_bomb);active_bomb=nullptr;
    process_chain->remove(update_node);process_chain->remove(draw_node);
}
void BombController::select_context(std::int32_t index) {
    view_index=index;context=&session.context(view_index);
}
std::int32_t BombController::initialize(std::int32_t index) {
    update_node=register_update(33,update_callback,this);
    draw_node=register_draw(44,draw_callback,this);
    age=0;active_bomb=nullptr;select_context(index);return 0;
}
std::int32_t BombController::draw() {
    if (active_bomb) active_bomb->draw();
    return 1;
}
std::int32_t BombController::event(const Vector3* position,const Vector2* dimensions) {
    if (active_bomb) active_bomb->event(position,dimensions);
    return 0;
}
std::int32_t BombController::finish() {return active_bomb?active_bomb->finish():0;}
std::int32_t BombController::update_callback(void* owner) {
    return static_cast<BombController*>(owner)->update();
}
std::int32_t BombController::draw_callback(void* owner) {
    return static_cast<BombController*>(owner)->draw();
}
BombController* bomb_controller(std::int32_t index) {return session.context(index).bomb_controller();}
}
