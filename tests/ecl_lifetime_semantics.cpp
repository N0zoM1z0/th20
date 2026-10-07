#include "EclRuntime.hpp"
#include "DiagnosticAllocator.hpp"
#include <algorithm>
#include <cassert>
#include <memory_resource>
#include <thread>
#include <vector>

namespace th20 {
LockRegistry process_locks;
DiagnosticAllocator* process_allocator;
// Original process allocator construction/startup remains a fixture boundary.
DiagnosticAllocator::DiagnosticAllocator() : state_word_(0), resource_() {}
}

namespace {
bool another_thread_can_lock() {
    bool available = false;
    std::thread worker([&] {
        auto& lock = th20::process_locks.slot(1);
        available = lock.try_lock();
        if (available) lock.unlock();
    });
    worker.join();
    return available;
}
struct TrackingResource : std::pmr::memory_resource {
    struct Allocation { void* pointer; std::size_t bytes, alignment; };
    std::vector<Allocation> live;
    std::vector<void*> retired;
    unsigned allocations = 0;
    bool inspect_lock = false;
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        void* result = std::pmr::new_delete_resource()->allocate(bytes, alignment);
        live.push_back({result, bytes, alignment});
        ++allocations;
        return result;
    }
    void do_deallocate(void* pointer, std::size_t bytes, std::size_t alignment) override {
        auto found = std::find_if(live.begin(), live.end(),
            [=](const Allocation& a) { return a.pointer == pointer; });
        assert(found != live.end() && found->bytes == bytes && found->alignment == alignment);
        // Runtime-owned PMR storage must be destroyed before the allocator's
        // slot-1 lock begins. Check ownership from a different thread because
        // the original lock is recursive.
        if (inspect_lock) assert(another_thread_can_lock());
        retired.push_back(pointer);
        live.erase(found);
        std::pmr::new_delete_resource()->deallocate(pointer, bytes, alignment);
    }
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }
};
void check_runtime_zero(const th20::EclRuntime& runtime, TrackingResource& resource) {
    assert(runtime.time == 0 && runtime.position.subroutine == 0 && runtime.position.offset == 0);
    assert(runtime.async_id == 0 && runtime.signal == 0 && runtime.rank == 0);
    assert(runtime.flags.bits == 0 && runtime.manager == nullptr);
    assert(runtime.stack.pointer == 0 && runtime.stack.frame_base == 0);
    assert(runtime.stack.words.empty() && runtime.interpolators.empty());
    assert(runtime.stack.words.get_allocator().resource() == &resource);
    assert(runtime.interpolators.get_allocator().resource() == &resource);
}
void reserve_runtime(th20::EclRuntime& runtime, unsigned count, std::vector<void*>& expected) {
    runtime.stack.words.resize(count);
    runtime.interpolators.reserve(count);
    expected.push_back(runtime.interpolators.data());
    expected.push_back(runtime.stack.words.data());
}
struct DestructionProbe {
    unsigned* count;
    ~DestructionProbe() {
        assert(another_thread_can_lock());
        ++*count;
    }
};
}

int main() {
    th20::DiagnosticAllocator allocator;
    th20::process_allocator = &allocator;
    allocator.release_object(static_cast<th20::EclRuntime*>(nullptr));
    allocator.release_object(static_cast<th20::IntrusiveLink<th20::EclRuntime>*>(nullptr));
    unsigned destructions = 0;
    allocator.release_object(new DestructionProbe{&destructions});
    assert(destructions == 1);

    TrackingResource primary, secondary;
    auto* previous = std::pmr::set_default_resource(&primary);
    primary.inspect_lock = true;
    std::vector<void*> expected;
    {
        th20::EclManager manager;
        check_runtime_zero(manager.main, primary);
        assert(primary.allocations == 0);
        assert(manager.field_04 == 0 && manager.field_08 == 0);
        assert(manager.current_runtime == nullptr && manager.loader == nullptr);
        assert(manager.runtimes.node == nullptr && manager.runtimes.next == nullptr);
        assert(manager.runtimes.previous == nullptr && manager.runtimes.owner == nullptr);
        assert(manager.runtimes.iterator == nullptr);
        assert(manager.execute_opcode() == 0 && manager.read_integer(-17) == 0);
        assert(manager.integer_destination(-17) == nullptr);
        assert(manager.read_float(-17) == 0.0f && manager.float_destination(-17) == nullptr);
        manager.terminate_async();

        auto* last = &manager.runtimes;
        for (unsigned i = 1; i <= 3; ++i) {
            auto* runtime = new th20::EclRuntime;
            check_runtime_zero(*runtime, primary);
            reserve_runtime(*runtime, i, expected);
            auto* link = new th20::IntrusiveLink<th20::EclRuntime>(runtime);
            last->insert_after(link);
            last = link;
        }
        auto* stale = manager.runtimes.next;
        // Changing the default resource must not redirect captured ownership.
        std::pmr::set_default_resource(&secondary);
        manager.terminate_async();
        assert(primary.retired == expected && primary.live.empty());
        assert(secondary.allocations == 0 && secondary.retired.empty());
        assert(manager.runtimes.next == stale); // Compare only; never dereference.
        manager.main.flags.bits = 0xa5;
        manager.main.rank = 0x7e;
        manager.reset();
        assert(manager.runtimes.next == nullptr && manager.runtimes.node == &manager.main);
        assert(manager.current_runtime == &manager.main && manager.main.manager == &manager);
        assert(manager.main.position.subroutine == -1 && manager.main.position.offset == -1);
        assert(manager.main.async_id == -1 && manager.main.signal == 0);
        assert(manager.main.flags.bits == 0xa4 && manager.main.rank == 0x7e);
        reserve_runtime(manager.main, 4, expected);
        assert(primary.allocations == 8 && secondary.allocations == 0);
        // The real destructor clears async nodes, then destroys main's
        // interpolation vector before main's stack vector.
    }
    assert(primary.live.empty() && primary.retired == expected);
    assert(secondary.live.empty() && secondary.allocations == 0);
    std::pmr::set_default_resource(previous);

    // Deletion through the actual manager virtual destructor also owns async
    // runtimes, while leaving the embedded main runtime with its parent.
    previous = std::pmr::set_default_resource(&primary);
    auto* manager = new th20::EclManager;
    auto* runtime = new th20::EclRuntime;
    expected.clear();
    reserve_runtime(*runtime, 2, expected);
    manager->runtimes.insert_after(new th20::IntrusiveLink<th20::EclRuntime>(runtime));
    const auto before = primary.retired.size();
    delete manager;
    assert(primary.live.empty() && primary.retired.size() == before + 2);
    assert(primary.retired[before] == expected[0] && primary.retired[before + 1] == expected[1]);
    std::pmr::set_default_resource(previous);
}
