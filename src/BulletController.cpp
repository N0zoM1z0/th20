#include "Bullet.hpp"
#include "EclDiagnostic.hpp"
#include "Session.hpp"
namespace th20 {
BulletExtendedCommands::BulletExtendedCommands() noexcept {}
BulletPool::BulletPool() {}
BulletHandles::BulletHandles() noexcept {}
BulletController::BulletController() noexcept
    :next_bullet(nullptr),draw_heads{nullptr},draw_tails{nullptr},bullet_count(0),field_48(0),age(0),
     item_counter(0),field_286d84(0),cancel_counter(0),file(nullptr),
     field_286d90(0),field_286d94(0),field_286d98(0),view_index(0),context(nullptr) {
    ecl_diagnostic_hint("initialize BulletInf\n");
}
BulletPool::~BulletPool() = default;
Bullet* BulletPool::begin() {return slots;}
Bullet* BulletPool::end() {return slots+2001;}
void BulletController::disable() {
    if(update_node) update_node->disable();
    if(draw_node) draw_node->disable();
    for(auto& bullet:pool) bullet.metadata.reset();
}
void BulletController::select_context(std::int32_t index) {
    view_index=index;
    context=&session.context(view_index);
}
std::int32_t BulletController::count() {return bullet_count;}
BulletController* bullet_controller(std::int32_t index) {
    return session.context(index).bullet_controller();
}
}
