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
// Owned host allocator startup fixture; callback retirement uses the real
// null-safe shared release_object template.
LockRegistry process_locks;
DiagnosticAllocator* process_allocator;
DiagnosticAllocator::DiagnosticAllocator() : state_word_(0), resource_() {}
// Logical identity value for portable execution only. This does not reconstruct
// the native constant's production initialization or accept a data unit.
const Matrix4 identity_matrix = [] {
    Matrix4 value;
    for (int i = 0; i < 4; ++i) value.elements[i][i] = 1.0f;
    return value;
}();
}

int main() {
    using namespace th20;
    DiagnosticAllocator allocator;
    process_allocator = &allocator;
    unsigned cases = 0;
    for (unsigned seed = 0; seed < 256; ++seed) {
        for (unsigned operation = 0; operation < 4; ++operation) {
            std::array<Animation, 33> animations;
            std::array<int, 33> parents;
            parents.fill(-1);
            for (unsigned i = 1; i < 32; ++i) {
                unsigned parent = (seed % 3 == 0) ? i - 1 :
                    (seed % 3 == 1) ? 0 : (i - 1) / 2;
                parents[i] = static_cast<int>(parent);
                animations[parent].child_links[1].insert_after(&animations[i].child_links[0]);
                animations[i].parent_558 = &animations[parent];
            }
            const unsigned selected = seed % 32;
            std::array<AnimationFlags, 33> before;
            for (unsigned i = 0; i < 33; ++i) {
                auto& a = animations[i];
                auto* bytes = reinterpret_cast<unsigned char*>(&a.base.flags);
                for (unsigned j = 0; j < sizeof(a.base.flags); ++j)
                    bytes[j] = static_cast<unsigned char>(seed * 7 + i * 13 + j * 17);
                before[i] = a.base.flags;
            }
            switch (operation) {
            case 0: animations[selected].clear_flag0_recursively(); break;
            case 1: animations[selected].set_flag0_recursively(); break;
            case 2: animations[selected].clear_flag_4b4_recursively(); break;
            case 3: animations[selected].set_flag_4b4_recursively(); break;
            }
            for (unsigned i = 0; i < 33; ++i) {
                bool descendant = false;
                for (int ancestor = static_cast<int>(i); ancestor >= 0; ancestor = parents[ancestor])
                    if (ancestor == static_cast<int>(selected)) descendant = true;
                auto expected = before[i];
                if (descendant) {
                    auto& word = operation < 2 ? expected.word_04 : expected.word_1c;
                    if (operation % 2) word |= 1u; else word &= ~1u;
                }
                assert(std::memcmp(&expected, &animations[i].base.flags, sizeof(expected)) == 0);
                auto& a = animations[i];
                for (auto* link : {&a.link_4ec, &a.link_500, &a.child_links[0], &a.child_links[1], &a.link_53c}) {
                    assert(link->node == &a && link->owner == nullptr && link->iterator == nullptr);
                }
                if (parents[i] >= 0) assert(a.parent_558 == &animations[parents[i]]);
                else assert(a.parent_558 == nullptr);
            }
            // Detach while every observed node and owner is still alive.
            for (auto& a : animations) a.child_links[0].detach();
            for (auto& a : animations) assert(a.child_links[1].next == nullptr);
            ++cases;
        }
    }
    Animation value;
    IntrusiveLink<Animation> empty(nullptr), next(&value);
    empty.insert_after(&next);
    {
        auto it = empty.begin();
        assert(!it.differs(empty.end()));
        assert(empty.iterator == nullptr && next.iterator == nullptr);
    }
    next.detach();
    ++cases;
    assert(cases == 1025);
}
