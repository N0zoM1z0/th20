#include "DebugAllocator.hpp"
#include "ShotMetadata.hpp"
#include <cassert>
#include <chrono>
#include <future>
#include <memory>
#include <memory_resource>
#include <thread>
#include <type_traits>
#include <utility>

namespace th20 {
// Owned fixture: the production global's definition/startup remains pending.
LockRegistry process_locks;
}

namespace {
struct Resource : std::pmr::memory_resource {
    unsigned live = 0;
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        auto* memory = std::pmr::new_delete_resource()->allocate(bytes, alignment);
        ++live;
        return memory;
    }
    void do_deallocate(void* memory, std::size_t bytes, std::size_t alignment) override {
        assert(live);
        --live;
        std::pmr::new_delete_resource()->deallocate(memory, bytes, alignment);
    }
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }
};

template<class Operation>
void requires_slot_one(Operation operation) {
    using namespace std::chrono_literals;
    std::unique_lock guard(th20::process_locks.slot(1));
    std::promise<void> entered, finished;
    auto entered_result = entered.get_future();
    auto finished_result = finished.get_future();
    std::thread worker([&] {
        entered.set_value();
        operation();
        finished.set_value();
    });
    entered_result.get();
    assert(finished_result.wait_for(20ms) == std::future_status::timeout);
    guard.unlock();
    assert(finished_result.wait_for(2s) == std::future_status::ready);
    finished_result.get();
    worker.join();
}

void allocation_lock_protocol() {
    DebugAllocator<int> allocator;
    int* values = nullptr;
    requires_slot_one([&] { values = allocator.allocate(3); });
    for (int i = 0; i != 3; ++i) std::construct_at(values + i, i * 7);
    assert(values[0] == 0 && values[1] == 7 && values[2] == 14);
    for (int i = 0; i != 3; ++i) std::destroy_at(values + i);
    requires_slot_one([&] { allocator.deallocate(values, 3); });
    // The same mutex is recursive, including when callers already own it.
    std::lock_guard guard(th20::process_locks.slot(1));
    values = allocator.allocate(1);
    allocator.deallocate(values, 1);
}

void shared_lifetimes(Resource& first, Resource& second) {
    DebugAllocator<EtamaArgInf> allocator;
    auto original = std::allocate_shared<EtamaArgInf>(allocator);
    assert(original.use_count() == 1 && first.live == 1);
    assert(original->commands.size() == 2 && original->sound == 21);
    std::weak_ptr<EtamaArgInf> weak(original);
    std::shared_ptr<void> erased(original);
    assert(original.use_count() == 2 && erased.get() == original.get());
    original->commands.resize(5);
    original->commands[3].opcode = 24;
    original->commands[3].script = "owned allocation fixture";
    original->field_20 = 3.5f;
    original->field_49 = true;
    auto* old_buffer = original->commands.data();

    std::pmr::set_default_resource(&second);
    auto clone = std::allocate_shared<EtamaArgInf>(allocator, *original);
    assert(clone.use_count() == 1 && original.use_count() == 2);
    assert(clone.get() != original.get() && clone->commands.data() != old_buffer);
    assert(clone->commands.get_allocator().resource() == &second);
    assert(original->commands.get_allocator().resource() == &first);
    assert(clone->commands.size() == 5 && clone->commands[3].opcode == 24);
    assert(clone->commands[3].script == original->commands[3].script);
    assert(clone->field_20 == 3.5f && clone->field_49);
    clone->commands[3].opcode = -7;
    assert(original->commands[3].opcode == 24);
    std::shared_ptr<EtamaArgInf> destination;
    auto* copied_payload = clone.get();
    destination = std::move(clone);
    assert(!clone && destination.get() == copied_payload && destination.use_count() == 1);

    original.reset();
    assert(!weak.expired() && first.live == 1);
    erased.reset();
    // Weak references retain the control block, never the managed command owner.
    assert(weak.expired() && first.live == 0 && !weak.lock());
    weak.reset();
    destination.reset();
    assert(second.live == 0);
    std::pmr::set_default_resource(&first);
}
}

int main() {
    static_assert(std::is_same_v<th20::ShotMetadata, EtamaArgInf>);
    static_assert(std::is_empty_v<DebugAllocator<EtamaArgInf>>);
    static_assert(std::is_trivially_default_constructible_v<DebugAllocator<EtamaArgInf>>);
    static_assert(!std::is_nothrow_constructible_v<DebugAllocator<int>, const DebugAllocator<double>&>);
    assert(DebugAllocator<int>{} == DebugAllocator<double>{});
    allocation_lock_protocol();
    Resource first, second;
    auto* previous = std::pmr::set_default_resource(&first);
    shared_lifetimes(first, second);
    std::pmr::set_default_resource(previous);
    assert(first.live == 0 && second.live == 0);
}
