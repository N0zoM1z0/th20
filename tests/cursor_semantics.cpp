#include "Cursor.hpp"
#include "PauseFlags.hpp"

#include <cassert>
#include <limits>
#include <memory_resource>
#include <array>
#include <cstring>
#include <new>

namespace {
class CountingResource final : public std::pmr::memory_resource {
public:
    unsigned live = 0;
private:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        void* allocation = std::pmr::new_delete_resource()->allocate(bytes, alignment);
        ++live;
        return allocation;
    }
    void do_deallocate(void* allocation, std::size_t bytes, std::size_t alignment) override {
        std::pmr::new_delete_resource()->deallocate(allocation, bytes, alignment);
        --live;
    }
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }
};
}

void check_cursor_history() {
    for (const auto pattern : {0x00000000u, 0xffffffffu, 0xaaaaaaaaU, 0x55555555u}) {
        alignas(th20::PauseFlags) std::array<unsigned char, 4> storage;
        std::memcpy(storage.data(), &pattern, 4);
        auto* flags = new (storage.data()) th20::PauseFlags;
        std::uint32_t actual;
        std::memcpy(&actual, storage.data(), 4);
        assert(actual == (pattern & ~7u));
        assert(flags->mode == 0 && flags->practice == 0);
        flags->~PauseFlags();
    }
    CountingResource resource;
    auto* old_resource = std::pmr::set_default_resource(&resource);
    {
        th20::Cursor cursor;
        assert(cursor.current == 0 && cursor.previous == 0 && cursor.count == 999);
        assert(cursor.minimum == 0 && cursor.wrapping == 1);
        assert(cursor.excluded.get_allocator().resource() == &resource);
        cursor.current = std::numeric_limits<std::int32_t>::min();
        cursor.snapshot();
        assert(cursor.changed() == 0 && cursor.selected(cursor.current) == 1);
        cursor.current = std::numeric_limits<std::int32_t>::max();
        assert(cursor.changed() == 1 && cursor.selected(cursor.previous) == 0);
        cursor.set_wrapping(-7);
        cursor.minimum = -9;
        cursor.excluded.push_back(3);
        const auto capacity = cursor.excluded.capacity();
        // Enough frames to grow the default deque block map, then fully unwind.
        for (int frame = 0; frame != 4096; ++frame) {
            cursor.current = frame - 2048;
            cursor.set_count(frame + 1);
            cursor.excluded.push_back(frame);
            cursor.save();
            assert(cursor.excluded.empty());
        }
        assert(cursor.selection_history.size() == 4096);
        assert(cursor.count_history.size() == 4096);
        cursor.previous = 12345;
        for (int frame = 4095; frame >= 0; --frame) {
            cursor.current = -9999;
            cursor.set_count(-9999);
            cursor.excluded.push_back(-1);
            cursor.restore();
            assert(cursor.current == frame - 2048 && cursor.count == frame + 1);
            assert(cursor.excluded.empty() && cursor.excluded.capacity() >= capacity);
            assert(cursor.previous == 12345 && cursor.minimum == -9 && cursor.wrapping == -7);
        }
        assert(cursor.selection_history.empty() && cursor.count_history.empty());
        cursor.excluded.push_back(2);
        cursor.restore();
        assert(cursor.current == -2048 && cursor.count == 1 && cursor.excluded.empty());
        assert(resource.live != 0); // clear retains the vector allocation.
    }
    assert(resource.live == 0); // Real PMR ownership is released by destruction.
    std::pmr::set_default_resource(old_resource);
}
