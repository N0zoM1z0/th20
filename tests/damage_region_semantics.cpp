#include "DamageRegion.hpp"
#include "ClockScalar.hpp"
#include <type_traits>
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>

using namespace th20;
namespace {
unsigned retire_calls;
DamageRegion* retired_region;
}
// Focused region checks observe the retirement call boundary here. The separate
// hit_controller_semantics fixture links the actual controller/allocator/region
// retirement bodies; this observation does not simulate retirement or deletion.
void th20::DamageRegion::retire() { ++retire_calls; retired_region = this; }
static_assert(std::is_nothrow_constructible_v<DamageRegion>);
static_assert(std::is_nothrow_constructible_v<IntrusiveIterator<DamageRegion>, IntrusiveLink<DamageRegion>*>);


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
    Vector3 quotient(9, -6, 3);
    assert(&(quotient /= 3) == &quotient);
    assert(quotient.x == 3 && quotient.y == -2 && quotient.z == 1);
    region.motion.position = Vector3(8, 6, 4);
    Vector3 copy = region.motion.position_copy();
    copy /= 2;
    assert(copy.x == 4 && copy.z == 2 && region.position().x == 8 && region.position().z == 4);

    region.motion.flags.bits = 0x20; // Motion alone is frozen; region time still advances.
    region.radius_a = 4; region.value_20 = 1.5f; region.radius_b = 9;
    region.angle = 0; region.angular_velocity = 0.25f;
    region.target = 123u; region.timer = 3; region.cooldown = 2;
    region.update();
    assert(region.position().x == 8 && region.position().z == 4);
    assert(region.radius_a == 5.5f && region.radius_b == 9 && region.angle.value == 0.25f);
    assert(region.target.get() == 0 && region.timer.current == 2 && region.cooldown == 1);
    assert(retire_calls == 0);
    region.update();
    assert(region.timer.current == 1 && region.cooldown == 0 && retire_calls == 0);
    region.update();
    assert(region.timer.current == 0 && region.cooldown == -1 && retire_calls == 1 && retired_region == &region);
    ClockScalar stopped(0);
    ClockScalar* saved_clock = timer_clock_sources[0];
    timer_clock_sources[0] = &stopped;
    region.timer = 1; region.cooldown = std::numeric_limits<std::int32_t>::min();
    region.update();
    assert(region.timer.current == 1 && region.cooldown == std::numeric_limits<std::int32_t>::max());
    assert(region.radius_a == 10 && region.angle.value == 1 && retire_calls == 1);
    region.timer = -2;
    region.update();
    assert(retire_calls == 2 && region.timer.current == -2);
    timer_clock_sources[0] = saved_clock;

    IntrusiveList<DamageRegion> list;
    DamageRegion first_node, second_node, third_node;
    list.append(&first_node.link); list.append(&second_node.link); list.append(&third_node.link);
    assert(list.tail == &third_node.link && first_node.link.previous == &list);
    assert(first_node.link.owner == &list && second_node.link.owner == &list);
    assert(list.find(&second_node) == &second_node.link && list.find(&region) == nullptr);
    assert(list.find(nullptr) == &list);
    assert(first_node.link.node_access() == &first_node);
    {
        auto iterator = list.begin();
        assert(iterator.differs(list.end()) && iterator.get() == &first_node.link);
        assert(first_node.link.iterator == &iterator && second_node.link.iterator == &iterator);
        second_node.link.detach(); // Repair the pending observer before advancing.
        assert(iterator.pending == &third_node.link && third_node.link.iterator == &iterator);
        assert(!second_node.link.owner && !second_node.link.next && !second_node.link.previous && !second_node.link.iterator);
        first_node.link.detach(); // A removed current node can still advance to the pending node.
        assert(iterator.current == nullptr && iterator.pending == &third_node.link);
        assert(&iterator.advance() == &iterator && iterator.get() == &third_node.link);
        assert(iterator.pending == nullptr && third_node.link.previous == &list);
        third_node.link.detach();
        assert(!iterator.differs(nullptr) && list.tail == &list && !list.next);
    }
    list.append(&first_node.link); list.append(&second_node.link);
    {
        auto iterator = list.begin();
        assert(iterator.current == &first_node.link && iterator.pending == &second_node.link);
    }
    assert(!first_node.link.iterator && !second_node.link.iterator);
    first_node.link.detach(); second_node.link.detach();
    list.reset(nullptr);
    assert(list.tail == &list && !list.next && !list.previous);
    second_node.link.initialize(&third_node);
    assert(second_node.link.node_value() == &third_node && !second_node.link.owner);
    assert(second_node.link.find(&third_node) == &second_node.link);
    IntrusiveIterator<DamageRegion> empty(nullptr), another_empty(nullptr);
    assert(!empty.differs(&another_empty) && !empty.differs(nullptr));
    empty.advance();
    assert(empty.get() == nullptr && empty.pending == nullptr);

}
