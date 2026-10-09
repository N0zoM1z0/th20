#include "WeaponStoneInfo.hpp"
namespace th20 {
WeaponStoneInfo::WeaponStoneInfo()
    :animation_file(nullptr),weapon_28(nullptr),weapon_2c(nullptr),weapon_30(nullptr),weapon_34(nullptr),
     mesh(nullptr),phase(0),radius(0),byte_78(0),view_index(0),context(nullptr) {}
bool WeaponStoneInfo::phase_one() {return phase==1?1:0;}
void WeaponStoneInfo::disable() {TaskInfo::disable();}
}
