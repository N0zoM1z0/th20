#include "Item.hpp"
#include "GameController.hpp"
namespace th20 {
extern GameController* current_game_controller;
std::int32_t ItemInf::update_callback(void* owner) {
    if (current_game_controller!=nullptr && current_game_controller->update_suppressed()!=0)
        return 1;
    if (current_game_controller!=nullptr &&
        ((current_game_controller->game_flags.bits>>11)&1u)!=0)
        return 1;
    return static_cast<ItemInf*>(owner)->update_main();
}
}
