#include "DamageRegion.hpp"
#include "CollisionGeometry.hpp"

namespace th20 {
// Native shared exception metadata corroborates nonthrowing construction.
DamageRegion::DamageRegion() noexcept : link(this), flags{},radius_a(0),radius_b(0),value_20(0),
    angle(),angular_velocity(0),dimensions(),motion(),timer(),identifier(),value_90(0),damage(0),
    value_98(0),value_9c(0),value_a0(0),target(),cooldown(0),group(0),animation(),value_b4(0),
    sides(0),value_bc(0),context(nullptr) {}

bool DamageRegion::intersects(const Vector3* center,const Vector2* size,float direction,float radius) {
    using namespace geometry;
    if (flags.fields.kind==0) {
        if (size) {
            if (rectangle_rectangle(motion.position_ref().x,motion.position_ref().y,dimensions.x,dimensions.y,
                                    angle,center->x,center->y,size->x,size->y,direction)) return true;
        } else {
            if (rectangle_circle(motion.position_ref().x,motion.position_ref().y,dimensions.x,dimensions.y,
                                 angle,center->x,center->y,radius)) return true;
        }
    } else if (flags.fields.kind==1) {
        if (size) {
            if (rectangle_circle(center->x,center->y,size->x,size->y,direction,
                                 motion.position_ref().x,motion.position_ref().y,radius_a)) return true;
        } else {
            if ((radius_a+radius)*(radius_a+radius)>=squared_distance_xy(motion.position_ref(),*center)) return true;
        }
    } else if (flags.fields.kind==2) {
        if (size) {
            if (rectangle_ellipse(center->x,center->y,size->x,size->y,direction,
                                  motion.position_ref().x,motion.position_ref().y,dimensions.x,dimensions.y,angle)) return true;
        } else {
            if (circle_ellipse(center->x,center->y,radius,motion.position_ref().x,motion.position_ref().y,
                               dimensions.x,dimensions.y,angle)) return true;
        }
    } else if (flags.fields.kind==3) {
        if (size) {
            if (rectangle_regular_polygon(center->x,center->y,size->x,size->y,direction,
                 motion.position_ref().x,motion.position_ref().y,radius_a,angle,sides)) return true;
        } else {
            if (circle_regular_polygon(center->x,center->y,radius,motion.position_ref().x,motion.position_ref().y,
                                       radius_a,angle,sides)) return true;
        }
    } else if (flags.fields.kind==4) {
        if (size) {
            if (rectangle_star(center->x,center->y,size->x,size->y,direction,
                 motion.position_ref().x,motion.position_ref().y,radius_a,radius_b,angle,sides)) return true;
        } else {
            if (circle_star(center->x,center->y,radius,motion.position_ref().x,motion.position_ref().y,
                           radius_a,radius_b,angle,sides)) return true;
        }
    }
    return false;
}
Vector3& DamageRegion::position() { return motion.position_ref(); }
Context* DamageRegion::context_value() { return context; }
bool DamageRegion::is_heap() { return (identifier.get()&0x01000000u)?true:false; }
void DamageRegion::set_position(const Vector3& input) {
    Motion& state=motion;
    state.set_position(input);
}
std::uint32_t DamageRegion::configure_rectangle(const Vector3& center,float width,float height,float direction,
                                               std::int32_t duration,std::int32_t input_damage) {
    flags.fields.active=1;
    flags.fields.kind=0;
    flags.fields.bit4=0;
    flags.fields.bit6=0;
    motion.clear();
    set_position(center);
    dimensions.x=width;
    dimensions.y=height;
    angle=direction;
    angular_velocity=0;
    timer=duration;
    damage=input_damage;
    value_98=0;
    value_9c=9999999;
    value_a0=1;
    value_b4=0;
    target=0u;
    cooldown=0;
    group=0;
    return identifier.get();
}
std::uint32_t DamageRegion::configure_circle(const Vector3& center,float radius,float value,
                                            std::int32_t duration,std::int32_t input_damage) {
    flags.fields.active=1;
    flags.fields.kind=1;
    flags.fields.bit4=0;
    flags.fields.bit6=0;
    motion.clear();
    set_position(center);
    radius_a=radius;
    value_20=value;
    timer=duration;
    damage=input_damage;
    value_98=0;
    value_9c=9999999;
    value_a0=1;
    value_b4=0;
    target=0u;
    cooldown=0;
    group=0;
    return identifier.get();
}
}

namespace th20 {
void DamageRegion::update() {
    motion.update();
    radius_a += value_20;
    angle += angular_velocity;
    target = 0u;
    Timer& lifetime = timer;
    lifetime--;
    cooldown = static_cast<std::int32_t>(static_cast<std::uint32_t>(cooldown) - 1u);
    const Timer& remaining = timer;
    if (remaining.at_most(0)) retire();
}
} // namespace th20
