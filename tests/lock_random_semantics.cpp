#include "GameRandom.hpp"
#include "LockRegistry.hpp"
#include <array>
#include <cassert>
#include <chrono>
#include <cstring>
#include <future>
#include <limits>
#include <thread>
#include <type_traits>

// Fixture-owned storage for the declared native global, with real mutexes.
namespace th20 { LockRegistry process_locks; }

static std::uint8_t depth(const th20::LockRegistry& locks, std::size_t index) {
    static_assert(std::is_standard_layout_v<th20::LockRegistry>);
    std::uint8_t result;
    // Observe the established trailing byte array; mutex size is host-specific.
    const auto* bytes = reinterpret_cast<const unsigned char*>(&locks);
    std::memcpy(&result, bytes + sizeof(std::recursive_mutex) * locks.count + index, 1);
    return result;
}

static bool available_to_other_thread(std::recursive_mutex& mutex) {
    return std::async(std::launch::async, [&mutex] {
        const bool acquired = mutex.try_lock();
        if (acquired) mutex.unlock();
        return acquired;
    }).get();
}

int main() {
    th20::LockRegistry locks;
    assert(!locks.enabled());
    for (std::size_t i = 0; i != locks.count; ++i) {
        assert(depth(locks, i) == 0);
        assert(available_to_other_thread(locks.slot(i)));
    }
    locks.enter_tracked(7);
    locks.leave_tracked(7);
    assert(depth(locks, 7) == 0 && available_to_other_thread(locks.slot(7)));
    locks.enable();
    for (unsigned i = 0; i != 256; ++i) {
        locks.enter_tracked(7);
        assert(depth(locks, 7) == static_cast<std::uint8_t>(i + 1));
    }
    assert(!available_to_other_thread(locks.slot(7)));
    assert(available_to_other_thread(locks.slot(8)));
    for (unsigned i = 0; i != 256; ++i) {
        locks.leave_tracked(7);
        assert(depth(locks, 7) == static_cast<std::uint8_t>(255 - i));
    }
    assert(available_to_other_thread(locks.slot(7)));
    locks.disable();

    constexpr std::uint32_t prime = 0x7fffffffu;
    for (std::uint32_t seed : std::array<std::uint32_t, 6>{0, 1, 2, prime - 1, prime, 0xffffffffu}) {
        th20::GameRandom random(42);
        random.field_00 = 0x89abcdefu;
        random.seed(seed);
        assert(random.minimum == 0 && random.upper == prime && random.modulus == prime);
        assert(random.last == seed && random.id == 42 && random.field_00 == 0x89abcdefu);
        std::uint64_t state = seed % prime;
        if (!state) state = 1;
        for (unsigned i = 0; i != 300; ++i) {
            state = (state * 48271u) % prime;
            assert(random.next() == state && random.last == state);
        }
        random.modulus = 13;
        state = (state * 48271u) % prime;
        assert(random.next() == state % 13 && random.last == state);
        assert(random.id == 42 && random.field_00 == 0x89abcdefu);
    }

    // Slot 10 is acquired even while tracked locking is disabled. Start the
    // worker before releasing the owned mutex, then verify completion/release.
    assert(!th20::process_locks.enabled());
    th20::GameRandom random(3);
    std::promise<void> started;
    auto entered = started.get_future();
    auto& mutex = th20::process_locks.slot(10);
    mutex.lock();
    auto pending = std::async(std::launch::async, [&] {
        started.set_value();
        random.seed(9);
        return random.next();
    });
    entered.get();
    assert(pending.wait_for(std::chrono::milliseconds(10)) == std::future_status::timeout);
    assert(available_to_other_thread(th20::process_locks.slot(11)));
    mutex.unlock();
    assert(pending.get() == 9u * 48271u);
    assert(available_to_other_thread(mutex));
}
