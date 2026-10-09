#include "Player.hpp"
#include "ShotData.hpp"
namespace th20 {
std::int32_t signed_resource_offset(std::uint32_t input) {
    return static_cast<std::int32_t>(input);
}
std::uint32_t relocated_resource_address(std::uint32_t offset,const void* base) {
    return offset+static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(base));
}
std::int32_t Player::load_shot_data(PlayerShotData** output,const char* path) {
    *output=reinterpret_cast<PlayerShotData*>(read_game_resource(path,nullptr,0));
    if (!*output) return -1;
    for (std::int32_t i=0;i<(*output)->entry_count;++i) {
        if (signed_resource_offset((*output)->entry_offsets[i])>=0) {
            auto address=relocated_resource_address((*output)->entry_offsets[i],*output);
            (*output)->entry_offsets[i]=address;
        }
    }
    return 0;
}
}
