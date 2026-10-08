#include "Bullet.hpp"
namespace th20 {
BulletColor::BulletColor():value(0) {}
Bullet::Bullet()
    :link(this),flags{},field_18(0),animation(nullptr),speed(0),field_24(0),
     index(0),field_2c(0),command_index(0),cancel_script(0),field_38(0),field_3c(0),
     field_40(0),draw_group(0),scale(0),field_4c(0),field_4e(0),state(0),field_54(0),
     style(nullptr),draw_next(nullptr),angle(0.0f),command_flags{},field_4d0(0),
     field_4d4(0),field_518(0),view_index(0),context(nullptr) {}
Bullet::~Bullet() = default;
}
