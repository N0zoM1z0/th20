#pragma once

#include <cstddef>
#include <cstdint>
#include <memory_resource>
#include <vector>

namespace th20 {

// Native script storage uses a PMR vector; offsets and frame bases are bytes.
struct ScriptStack {
    std::pmr::vector<std::uint32_t> words;
    std::int32_t pointer;
    std::int32_t frame_base;

    ScriptStack() noexcept;
    void reset();
    // Valid addresses resolve to nonnegative word indices. For local addresses,
    // frame_base + byte_offset must also be representable as int32_t.
    std::uint32_t& absolute(std::int32_t byte_offset);
    std::uint32_t& local(std::int32_t byte_offset);
    int leave_frame();
    int enter_frame(std::int32_t byte_count);
    std::int32_t frame_value() const;

    // Valid copies require sufficient readable/writable storage and representable
    // byte arithmetic. Pop and peek do not grow or bounds-check the word vector.
    // Tags occupy a full word; i/f tags request numeric conversion.
    int pop(std::int32_t byte_count, void* output, char requested_type);
    int peek(std::int32_t byte_offset, void* output, char requested_type);
    int push(std::int32_t byte_count, const void* input, char supplied_type);
    std::int32_t pointer_value() const;
    void set_pointer(std::int32_t value);
};

#if defined(_M_IX86)
static_assert(sizeof(ScriptStack) == 24);
static_assert(offsetof(ScriptStack, pointer) == 16);
static_assert(offsetof(ScriptStack, frame_base) == 20);
#endif

} // namespace th20
