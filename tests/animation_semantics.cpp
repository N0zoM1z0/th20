#include "Animation.hpp"
#include "DiagnosticAllocator.hpp"

#include <array>
#include <bit>
#include <cassert>
#include <cmath>
#include <cstring>
#include <limits>
#include <new>
#include <type_traits>

namespace {
th20::Animation* releasing;
th20::AnimationCallback* expected_callback;
unsigned callback_calls;
int callback_token;

template<class T> void check_padding(const T& object, std::size_t first,
                                    std::size_t end) {
    const auto* bytes = reinterpret_cast<const unsigned char*>(&object);
    for (std::size_t i = first; i < end; ++i) assert(bytes[i] == 0xa5);
}

template<class T> void stopped_only(th20::Interpolation<T>& value) {
    value.timer.set(19);
    value.duration = 73;
    value.mode = 91;
}

template<class T> void retained_sample(const th20::Interpolation<T>& value) {
    assert(value.duration == 0 && value.mode == 91);
    assert(value.timer.current == 19);
}
}

namespace th20 {
// Owned host startup fixture, shared with the archive tests. Production startup
// and callback virtual destruction remain unresolved; this test observes the
// callback argument and order without dereferencing its opaque token.
LockRegistry process_locks;
DiagnosticAllocator* process_allocator;
DiagnosticAllocator::DiagnosticAllocator() : state_word_(0), resource_() {}
void DiagnosticAllocator::release_animation_callback(AnimationCallback* input) {
    assert(this == process_allocator);
    if (releasing) {
        assert(releasing->geometry == nullptr && releasing->geometry_bytes == 0);
        assert(releasing->callback == input && input == expected_callback);
        assert(releasing->handle.value == 0x12345678u);
        assert(releasing->base.field_28 == 37);
    }
    ++callback_calls;
}
// Logical identity value for portable execution only. This does not reconstruct
// the native constant's production initialization or accept a data unit.
const Matrix4 identity_matrix = [] {
    Matrix4 value;
    for (int i = 0; i < 4; ++i) value.elements[i][i] = 1.0f;
    return value;
}();
}

int main(int argc, char**) {
    using namespace th20;
    static_assert(std::is_nothrow_constructible_v<AnimationBase>);
    static_assert(std::is_nothrow_constructible_v<Animation>);
    static_assert(std::is_nothrow_destructible_v<Animation>);
    static_assert(!std::is_trivially_destructible_v<Animation>);
    DiagnosticAllocator allocator;
    process_allocator = &allocator;
    if (argc > 1) {
        Animation looping;
        looping.field_550 = 1;
        looping.release_resources();
        return 2; // The native nonzero-word path must not return.
    }

    alignas(PooledAnimation) std::array<unsigned char, sizeof(PooledAnimation)> storage;
    storage.fill(0xa5);
    auto* pooled = ::new (storage.data()) PooledAnimation;
    Animation& a = pooled->animation;
    assert(a.base.timer.current == 0 && a.handle.value == 0 && a.index == 0);
    assert(a.geometry == nullptr && a.callback == nullptr && a.geometry_bytes == 0);
    assert(a.parent_558 == nullptr && a.parent_55c == nullptr);
    for (auto* link : {&a.link_4ec, &a.link_500, &a.link_514, &a.link_528, &a.link_53c}) {
        assert(link->node == &a && link->next == nullptr && link->previous == nullptr);
        assert(link->owner == nullptr && link->iterator == nullptr);
    }
    assert(pooled->free_link.node == nullptr && pooled->free_link.next == nullptr);
    assert(pooled->free_link.previous == nullptr && pooled->free_link.owner == nullptr);
    assert(pooled->free_link.iterator == nullptr && pooled->active == 0 && pooled->index == 0);
    check_padding(a.base, offsetof(AnimationBase, field_440) + sizeof(a.base.field_440),
                  offsetof(AnimationBase, variables));
    check_padding(a, offsetof(Animation, field_579) + sizeof(a.field_579),
                  offsetof(Animation, matrix_57c));
    check_padding(*pooled, offsetof(PooledAnimation, active) + sizeof(pooled->active),
                  offsetof(PooledAnimation, index));
    assert(a.base.interpolation_1b4.current.value == 0.0f);
    for (const auto& row : a.base.matrix_3b8.elements)
        for (float value : row) assert(value == 0.0f);

    Animation parent, grandparent;
    a.base.vector_50 = {2.0f, -3.0f};
    a.base.vector_70 = {5.0f, 7.0f};
    parent.base.vector_50 = {4.0f, 6.0f};
    grandparent.base.vector_50 = {-0.5f, 2.0f};
    a.parent_558 = &parent;
    a.parent_55c = &grandparent; // Only +558 participates in scale inheritance.
    parent.parent_558 = &grandparent;
    assert(a.width() == -20.0f && a.height() == -252.0f);
    parent.base.flags.word_04 = 0x1000u;
    assert(a.width() == 40.0f && a.height() == -126.0f);
    a.base.flags.word_04 = 0x1000u;
    assert(a.width() == 10.0f && a.height() == -21.0f);
    a.base.vector_50.x = -0.0f;
    assert(std::signbit(a.width()));
    a.base.vector_50.y = std::numeric_limits<float>::quiet_NaN();
    assert(std::isnan(a.height()));
    a.position_ref().z = 23.0f;
    assert(a.base.vector_2c.z == 23.0f);

    // Dirty reset verifies retained state and ownership, not just default values.
    a.base.timer.set(31);
    a.base.field_28 = 37;
    a.base.field_10 = 123;
    a.base.variables.field_00 = 51;
    a.base.variables.field_34 = -7.0f;
    a.base.variables.field_38 = -9.0f;
    a.base.variables.field_3c = -1;
    a.base.color_494 = 0xabcdef12u;
    a.base.vector_398 = {71.0f, 72.0f};
    a.base.vectors_378[3] = {11.0f, 12.0f};
    a.base.matrix_3f8.elements[1][2] = 13.0f;
    a.matrix_57c.elements[2][1] = 14.0f;
    a.base.vector_484 = {1.0f, 2.0f, 3.0f};
    a.base.vector_80 = {4.0f, 5.0f, 6.0f};
    a.base.field_78 = a.base.field_7c = 17.0f;
    a.timer_4c8.set(42);
    a.timer_4d8.set(43);
    a.field_570 = 9;
    a.field_574 = 81;
    std::memset(&a.base.flags, 0xff, sizeof(a.base.flags));
    stopped_only(a.base.interpolation_8c);
    stopped_only(a.base.interpolation_e0);
    stopped_only(a.base.interpolation_134);
    stopped_only(a.base.interpolation_160);
    stopped_only(a.base.interpolation_1b4);
    stopped_only(a.base.interpolation_1e0);
    stopped_only(a.base.interpolation_220);
    stopped_only(a.base.interpolation_260);
    stopped_only(a.base.interpolation_2a0);
    stopped_only(a.base.interpolation_2f4);
    stopped_only(a.base.interpolation_320);
    stopped_only(a.base.interpolation_34c);
    a.geometry = allocator.allocate_bytes(64, "animation test");
    a.geometry_bytes = 64;
    a.callback = reinterpret_cast<AnimationCallback*>(&callback_token);
    a.handle = 0x12345678u;
    a.reset();
    assert(callback_calls == 0 && a.geometry != nullptr && a.geometry_bytes == 64);
    assert(a.callback == reinterpret_cast<AnimationCallback*>(&callback_token));
    assert(a.handle.value == 0x12345678u && a.base.timer.current == 31);
    assert(a.base.field_28 == 37 && a.base.field_10 == 123);
    assert(a.base.variables.field_00 == 51 && a.base.variables.field_34 == 1.0f);
    assert(std::bit_cast<std::uint32_t>(a.base.variables.field_38) == 0x40490fdbu);
    assert(a.base.variables.field_3c == 65536 && a.base.color_490 == 0xffffffffu);
    assert(a.base.color_494 == 0xabcdef12u && a.field_570 == 0 && a.field_574 == 81);
    assert(a.parent_558 == nullptr && a.parent_55c == nullptr);
    assert(a.timer_4c8.current == 0 && a.timer_4d8.current == 0);
    assert(a.base.vector_2c.z == 0 && a.base.vector_484.y == 0 && a.base.vector_80.x == 0);
    assert(a.base.vector_50.x == 1 && a.base.vector_50.y == 1);
    assert(a.base.vector_58.x == 1 && a.base.vector_68.y == 1);
    assert(a.base.vector_60.x == 0 && a.base.vector_70.y == 0);
    assert(a.base.field_78 == 0 && a.base.field_7c == 0);
    assert(a.base.vector_398.x == 71 && a.base.vectors_378[3].y == 12);
    assert(a.base.matrix_3f8.elements[1][2] == 13 && a.matrix_57c.elements[2][1] == 14);
    const auto* flag_bytes = reinterpret_cast<const unsigned char*>(&a.base.flags);
    for (unsigned i = 0; i < sizeof(a.base.flags); ++i)
        assert(flag_bytes[i] == ((i == 2 || i == 4 || i == 8) ? 1 : 0));
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            assert(a.base.matrix_3b8.elements[i][j] == (i == j ? 1.0f : 0.0f));
    retained_sample(a.base.interpolation_8c);
    retained_sample(a.base.interpolation_e0);
    retained_sample(a.base.interpolation_134);
    retained_sample(a.base.interpolation_160);
    retained_sample(a.base.interpolation_1b4);
    retained_sample(a.base.interpolation_1e0);
    retained_sample(a.base.interpolation_220);
    retained_sample(a.base.interpolation_260);
    retained_sample(a.base.interpolation_2a0);
    retained_sample(a.base.interpolation_2f4);
    retained_sample(a.base.interpolation_320);
    retained_sample(a.base.interpolation_34c);

    expected_callback = a.callback;
    releasing = &a;
    a.release_resources();
    releasing = nullptr;
    assert(callback_calls == 1 && a.callback == nullptr && a.handle.value == 0);
    assert(a.base.field_28 == -1 && a.base.field_10 == 123);
    assert(a.link_4ec.node == &a && a.base.timer.current == 31);
    pooled->~PooledAnimation();
    assert(callback_calls == 2); // The real nontrivial destructor invokes cleanup.
}
