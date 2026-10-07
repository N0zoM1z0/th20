#include "DamageRegion.hpp"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>

using namespace th20;

int main() {
    DamageRegion region;
    assert(region.link.node == &region && !region.link.next && !region.link.previous);
    assert(!region.link.owner && !region.link.iterator);
    assert(region.flags.bits == 0 && region.identifier.get() == 0);
    assert(!region.context_value() && &region.position() == &region.motion.position);
    assert(region.radius_a == 0 && region.radius_b == 0 && region.value_20 == 0);
    assert(region.dimensions.x == 0 && region.dimensions.y == 0);
    assert(region.cooldown == 0 && region.group == 0 && region.sides == 0);

    Identifier32 other;
    assert(region.identifier.equals(other) == 1);
    region.identifier = std::numeric_limits<std::uint32_t>::max();
    assert(region.identifier.get() == 0xffffffffu && region.identifier.equals(other) == 0);
    assert(region.is_heap());
    region.identifier = 0xfeffffffu;
    assert(!region.is_heap());
    region.identifier = 0x01000000u;
    assert(region.is_heap());
    other = 0x01000000u;
    assert(region.identifier.equals(other) == 1);

    region.motion.velocity = Vector3(4, 5, 6);
    region.set_position(region.motion.velocity);
    assert(region.position().x == 4 && region.position().y == 5 && region.position().z == 6);
    assert(region.motion.velocity.x == 4 && region.motion.velocity.z == 6);
    region.set_position(region.position());
    assert(region.position().z == 6);
    region.motion.flags.bits = 0xffffffffu;
    region.motion.clear();
    const auto* bytes = reinterpret_cast<const unsigned char*>(&region.motion);
    assert(std::all_of(bytes, bytes + sizeof(Motion), [](unsigned char b) { return b == 0; }));

    region.flags.bits = 0xffffffffu;
    region.radius_a = 11; region.radius_b = 12; region.value_20 = 13;
    region.value_90 = 14; region.value_bc = 15; region.sides = 6;
    region.animation = 16u;
    region.target = 999u; region.cooldown = 5; region.group = 3;
    region.motion.velocity = Vector3(1, 2, 3);
    const Vector3 origin(7, 8, 9);
    assert(region.configure_rectangle(origin, 6, 4, 0, -3, -7) == 0x01000000u);
    assert(region.flags.bits == ((0xffffffffu & ~0x5fu) | 1u));
    assert(region.position().x == 7 && region.position().y == 8 && region.position().z == 9);
    assert(region.motion.velocity.x == 0 && region.motion.flags.bits == 0);
    assert(region.dimensions.x == 6 && region.dimensions.y == 4);
    assert(region.angle.value == 0 && region.angular_velocity == 0);
    assert(region.timer.current == -3 && region.timer.previous == -4);
    assert(region.damage == -7 && region.value_98 == 0 && region.value_9c == 9999999);
    assert(region.value_a0 == 1 && region.value_b4 == 0 && region.target.get() == 0);
    assert(region.cooldown == 0 && region.group == 0);
    assert(region.radius_a == 11 && region.radius_b == 12 && region.value_20 == 13);
    assert(region.value_90 == 14 && region.value_bc == 15 && region.animation.get() == 16);

    region.angular_velocity = 0.25f;
    region.angle = 0.5f;
    const auto before_flags = region.flags.bits;
    assert(region.configure_circle(origin, 3, -0.75f, 20, 8) == 0x01000000u);
    assert(region.flags.bits == ((before_flags & ~0x5fu) | 3u));
    assert(region.radius_a == 3 && region.value_20 == -0.75f && region.radius_b == 12);
    assert(region.angle.value == 0.5f && region.angular_velocity == 0.25f);
    assert(region.dimensions.x == 6 && region.dimensions.y == 4);
    assert(region.timer.current == 20 && region.timer.previous == 19 && region.damage == 8);

    // Native clear happens before reading the supplied position reference.
    region.configure_circle(region.position(), 3, 0, 10, 1);
    assert(region.position().x == 0 && region.position().y == 0 && region.position().z == 0);

    region.angle = 0;
    region.dimensions = Vector2(6, 4);
    region.radius_a = 5; region.radius_b = 2; region.sides = 5;
    Vector3 near(0, 0, 9999), far(100, 100, -9999);
    const Vector2 query_size(1, 1);
    for (unsigned kind = 0; kind != 5; ++kind) {
        region.flags.bits = kind << 1; // Activation is owned by the caller.
        assert(region.intersects(&near, nullptr, 0, 0.1f));
        assert(region.intersects(&near, &query_size, 0, 0.1f));
        assert(!region.intersects(&far, nullptr, 0, 0.1f));
        assert(!region.intersects(&far, &query_size, 0, 0.1f));
        region.flags.bits |= 0xfffffff1u;
        assert(region.intersects(&near, nullptr, 0, 0.1f));
    }
    for (unsigned kind = 5; kind != 8; ++kind) {
        region.flags.bits = kind << 1;
        assert(!region.intersects(nullptr, nullptr, 0, 0));
        assert(!region.intersects(nullptr, &query_size, 0, 0));
    }
    region.flags.bits = 2;
    region.radius_a = 3;
    Vector3 tangent(5, 0, 777), outside(5.01f, 0, 0);
    assert(region.intersects(&tangent, nullptr, 0, 2));
    assert(!region.intersects(&outside, nullptr, 0, 2));

    region.flags.bits = 0;
    region.dimensions = Vector2(2, 8);
    region.angle = 1.5707963267948966f;
    Vector3 turned(3, 0, 0);
    assert(region.intersects(&turned, nullptr, 0, 0.1f));
    region.angle = 0;
    assert(!region.intersects(&turned, nullptr, 0, 0.1f));

    DamageRegion middle, last;
    region.link.insert_after(&last.link);
    last.link.insert_before(&middle.link);
    assert(region.link.next == &middle.link && middle.link.next == &last.link);
    assert(last.link.previous == &middle.link && middle.link.previous == &region.link);
    assert(last.link.node == &last && middle.link.node == &middle);
}
