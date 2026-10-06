#include "EnemyCounters.hpp"
#include "ScriptStack.hpp"

#include <array>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <memory_resource>
#include <new>

namespace {
int pop_calls;
int observed_pointer;
int observed_frame;
std::int32_t restored_frame;
}

// Test-only observation of the unresolved native dependency. This checks the
// caller's pointer, size, tag and ordering; it does not reconstruct generic pop.
int th20::ScriptStack::pop(std::int32_t byte_count, void* output, char tag) {
    assert(byte_count == 4 && tag == 0 && output == &frame_base);
    observed_pointer = pointer;
    observed_frame = frame_base;
    ++pop_calls;
    pointer -= 4;
    std::memcpy(output, &restored_frame, 4);
    return -17; // leave_frame always returns zero, regardless of this status.
}

void check_script_values() {
    th20::ScriptStack stack;
    assert(stack.words.empty() && stack.pointer == 0 && stack.frame_base == 0);
    assert(stack.words.get_allocator().resource() == std::pmr::get_default_resource());
    stack.absolute(19) = 0x12345678;
    assert(stack.words.size() == 5 && stack.words[4] == 0x12345678);
    for (unsigned i = 0; i != 4; ++i) assert(stack.words[i] == 0);
    assert(&stack.absolute(16) == &stack.absolute(19));
    stack.frame_base = 20;
    stack.local(-4) = 0xaabbccdd;
    assert(stack.words.size() == 5 && stack.words[4] == 0xaabbccdd);
    stack.local(15) = 0x87654321;
    assert(stack.words.size() == 9 && stack.words[8] == 0x87654321);
    assert(stack.words[4] == 0xaabbccdd);
    for (unsigned i = 5; i != 8; ++i) assert(stack.words[i] == 0);
    assert(stack.pointer == 0 && stack.frame_base == 20);
    stack.pointer = 108;
    stack.frame_base = 64;
    restored_frame = 20;
    assert(stack.leave_frame() == 0);
    assert(pop_calls == 1 && observed_pointer == 108 && observed_frame == 64);
    assert(stack.pointer == 64 && stack.frame_base == 20);

    alignas(th20::EnemyCounters) std::array<unsigned char, 48> storage;
    storage.fill(0xa5);
    auto* counters = ::new (storage.data()) th20::EnemyCounters;
    for (auto byte : storage) assert(byte == 0);
    // Arbitrary integer/float representations, including negative zero and
    // NaN payloads, are overwritten without interpreting their old values.
    const std::array<std::uint32_t, 12> dirty{
        1, 0xffffffff, 0x80000000, 0x12345678,
        0x80000000, 0x7fc12345, 0xff800000, 0x7f800000,
        0x3f800000, 0xbf800000, 0x7fa12345, 0xffffffff};
    std::memcpy(storage.data(), dirty.data(), sizeof(*counters));
    counters->reset();
    for (auto byte : storage) assert(byte == 0);
    counters->~EnemyCounters();
}
