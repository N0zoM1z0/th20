#include "EclRuntime.hpp"

#include <array>
#include <bit>
#include <cassert>
#include <cstring>
#include <limits>
#include <memory_resource>
#include <new>

namespace {
struct Record {
    th20::EclInstruction instruction{};
    std::array<std::uint32_t, 32> payload{};
} record;
static_assert(offsetof(Record, payload) == 16);
int loader_calls, seen_subroutine, seen_offset;
int integer_reads, float_reads, integer_writes, float_writes, variable;
std::int32_t integer_slot;
float float_slot;
std::uint32_t bits(float value) { return std::bit_cast<std::uint32_t>(value); }

struct Manager : th20::EclManager {
    std::int32_t read_integer(std::int32_t index) override {
        ++integer_reads; variable = index; return -321;
    }
    float read_float(std::int32_t index) override {
        ++float_reads; variable = index; return 6.25f;
    }
    std::int32_t* integer_destination(std::int32_t index) override {
        ++integer_writes; variable = index; return &integer_slot;
    }
    float* float_destination(std::int32_t index) override {
        ++float_writes; variable = index; return &float_slot;
    }
};

struct Resource : std::pmr::memory_resource {
    bool fail = false;
    int live = 0;
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        if (fail) throw std::bad_alloc();
        ++live;
        return std::pmr::new_delete_resource()->allocate(bytes, alignment);
    }
    void do_deallocate(void* ptr, std::size_t bytes, std::size_t alignment) override {
        --live;
        std::pmr::new_delete_resource()->deallocate(ptr, bytes, alignment);
    }
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }
};
}

// Explicit unresolved boundaries: original Runtime/Manager construction,
// resource instruction lookup and game variable dispatch. Real current(), all
// eleven resolvers, Stack copy/access/lifetime and base loader lifetime run here.
namespace th20 {
EclScriptPosition::EclScriptPosition() : subroutine(-1), offset(-1) {}
EclRuntime::EclRuntime()
    : time(0), async_id(-1), manager(nullptr), signal(-1), rank(0), flags(0) {}
EclManager::EclManager()
    : field_04(0), field_08(0), current_runtime(&main), loader(nullptr) {}
EclManager::~EclManager() = default;
std::int32_t EclManager::execute_opcode() { return 0; }
std::int32_t EclManager::read_integer(std::int32_t) { return 0; }
float EclManager::read_float(std::int32_t) { return 0; }
std::int32_t* EclManager::integer_destination(std::int32_t) { return nullptr; }
float* EclManager::float_destination(std::int32_t) { return nullptr; }
EclInstruction* EclLoader::instruction(std::int32_t subroutine, std::int32_t offset) {
    ++loader_calls; seen_subroutine = subroutine; seen_offset = offset;
    return &record.instruction;
}
}

void check_stack() {
    th20::ScriptStack stack;
    for (int length = 0; length <= 32; ++length) {
        std::array<std::uint32_t, 8> input, output;
        for (unsigned i = 0; i != input.size(); ++i) input[i] = 0x9a765400u + i;
        output.fill(0xa5a5a5a5);
        stack.pointer = 0;
        assert(stack.push(length, input.data(), 0) == 0);
        assert(stack.pointer == length && stack.words.size() >= unsigned((length + 4) / 4));
        assert(stack.pop(length, output.data(), 0) == 0 && stack.pointer == 0);
        assert(std::memcmp(input.data(), output.data(), length) == 0);
        const auto* bytes = reinterpret_cast<const unsigned char*>(output.data());
        for (unsigned i = length; i != sizeof(output); ++i) assert(bytes[i] == 0xa5);
    }
    for (char tag : std::array<char, 4>{0, 'i', 'f', static_cast<char>(0x80)}) {
        std::uint32_t input = 0x80000000, output = 0;
        stack.pointer = 0;
        stack.push(4, &input, tag);
        if (tag) assert(stack.words[0] == static_cast<std::uint32_t>(tag));
        assert(stack.pointer == (tag ? 8 : 4));
        stack.pop(4, &output, tag);
        assert(output == input && stack.pointer == 0);
    }
    for (float value : std::array<float, 4>{-3.75f, 0.0f, 6.75f, 1024.0f}) {
        stack.pointer = 0;
        stack.push(4, &value, 'f');
        std::int32_t integer = 99;
        const auto saved = stack.words;
        stack.peek(-8, &integer, 'i');
        assert(integer == static_cast<std::int32_t>(value));
        assert(stack.pointer == 8 && stack.words == saved);
        stack.pop(4, &integer, 'i');
        assert(integer == static_cast<std::int32_t>(value) && stack.pointer == 0);
    }
    for (std::int32_t value : std::array<std::int32_t, 4>{-123, 0, 123, 16777217}) {
        stack.pointer = 0;
        stack.push(4, &value, 'i');
        float result = 0;
        stack.peek(-8, &result, 'f');
        assert(result == static_cast<float>(value) && stack.pointer == 8);
        stack.pop(4, &result, 'f');
        assert(result == static_cast<float>(value) && stack.pointer == 0);
    }
    {
        const std::array<std::uint32_t, 2> input{bits(-3.75f), 0x89abcdef};
        std::array<std::uint32_t, 2> output{};
        stack.pointer = 0;
        stack.push(8, input.data(), 'f');
        assert(stack.pointer == 12);
        stack.pop(8, output.data(), 'i');
        assert(std::bit_cast<std::int32_t>(output[0]) == -3);
        assert(output[1] == input[1] && stack.pointer == 0);
        stack.push(8, input.data(), 'f');
        stack.pop(8, output.data(), 'x');
        assert(output == input && stack.pointer == 0);
    }
    stack.pointer = 0;
    std::int32_t frame = 20;
    stack.push(4, &frame, 0);
    stack.frame_base = 64;
    assert(stack.leave_frame() == 0 && stack.pointer == 64 && stack.frame_base == 20);

    Resource resource;
    auto* previous = std::pmr::set_default_resource(&resource);
    {
        th20::ScriptStack owned;
        resource.fail = true;
        try { owned.push(4, &frame, 'i'); assert(false); }
        catch (const std::bad_alloc&) {}
        assert(owned.words.empty() && owned.pointer == 0 && resource.live == 0);
        resource.fail = false;
        owned.push(4, &frame, 'i');
        assert(resource.live == 1 && owned.pointer == 8);
    }
    std::pmr::set_default_resource(previous);
    assert(resource.live == 0);
}

void check_runtime() {
    Manager manager;
    th20::EclLoader loader;
    auto& runtime = manager.main;
    runtime.manager = &manager;
    manager.loader = &loader;
    loader_calls = 0;
    assert(runtime.current() == nullptr && loader_calls == 0);
    runtime.position.subroutine = 7;
    assert(runtime.current() == nullptr && loader_calls == 0);
    runtime.position.offset = 48;
    assert(runtime.current() == &record.instruction);
    assert(loader_calls == 1 && seen_subroutine == 7 && seen_offset == 48);
    runtime.stack.words.resize(512);
    runtime.stack.frame_base = 16;
    for (int index = 0; index != 16; ++index) {
        record.instruction.references = 0;
        record.payload[index] = 0x80000000;
        runtime.stack.pointer = 800;
        assert(runtime.integer_argument(index) == std::numeric_limits<std::int32_t>::min());
        assert(runtime.consuming_integer(index) == std::numeric_limits<std::int32_t>::min());
        assert(bits(runtime.float_argument(index)) == 0x80000000);
        assert(bits(runtime.consuming_float(index)) == 0x80000000);
        const float nan = std::bit_cast<float>(0x7fc12345u);
        assert(bits(runtime.float_argument_value(index, nan)) == bits(nan));
        assert(bits(runtime.consuming_float_value(index, nan)) == bits(nan));
        assert(runtime.integer_argument_value(index, -77) == -77);
        assert(runtime.consuming_integer_value(index, -77) == -77);
        assert(runtime.integer_destination(index) == nullptr);
        assert(runtime.float_destination(index) == nullptr);
        assert(runtime.float_destination_at(&record.instruction, 32, index) == nullptr);
        assert(runtime.stack.pointer == 800);

        record.instruction.references = static_cast<std::uint16_t>(1u << index);
        record.payload[index] = 4;
        runtime.stack.words[5] = 12345;
        assert(runtime.integer_argument(index) == 12345);
        assert(runtime.consuming_integer(index) == 12345);
        assert(runtime.integer_argument_value(index, 4) == 12345);
        assert(runtime.consuming_integer_value(index, 4) == 12345);
        assert(runtime.integer_destination(index) == reinterpret_cast<std::int32_t*>(&runtime.stack.words[5]));
        record.payload[index] = bits(4.75f);
        runtime.stack.words[5] = bits(3.5f);
        assert(runtime.float_argument(index) == 3.5f);
        assert(runtime.consuming_float(index) == 3.5f);
        assert(runtime.float_argument_value(index, 4.75f) == 3.5f);
        assert(runtime.consuming_float_value(index, 4.75f) == 3.5f);
        assert(runtime.float_destination(index) == reinterpret_cast<float*>(&runtime.stack.words[5]));
        assert(runtime.float_destination_at(&record.instruction, 32, index) == reinterpret_cast<float*>(&runtime.stack.words[9]));

        // Both -1 forms peek eight bytes behind SP. Consuming entry points
        // pop the top regardless of the reference magnitude.
        runtime.stack.words[198] = 'f'; runtime.stack.words[199] = bits(-3.75f);
        runtime.stack.words[202] = 'i'; runtime.stack.words[203] = 42;
        runtime.stack.pointer = 800;
        record.payload[index] = static_cast<std::uint32_t>(-1);
        assert(runtime.integer_argument(index) == -3);
        assert(runtime.integer_argument_value(index, -1) == -3);
        record.payload[index] = bits(-1.0f);
        assert(runtime.float_argument(index) == -3.75f);
        assert(runtime.float_argument_value(index, -1.0f) == -3.75f);
        assert(runtime.stack.pointer == 800);
        assert(runtime.consuming_float(index) == -3.75f && runtime.stack.pointer == 792);
        runtime.stack.pointer = 800;
        assert(runtime.consuming_float_value(index, -99.0f) == -3.75f && runtime.stack.pointer == 792);
        runtime.stack.pointer = 800;
        record.payload[index] = static_cast<std::uint32_t>(-99);
        assert(runtime.consuming_integer(index) == -3 && runtime.stack.pointer == 792);
        runtime.stack.pointer = 800;
        assert(runtime.consuming_integer_value(index, -99) == -3 && runtime.stack.pointer == 792);

        runtime.stack.pointer = 800;
        runtime.stack.words[0] = 'i'; runtime.stack.words[1] = static_cast<std::uint32_t>(-7);
        record.payload[index] = static_cast<std::uint32_t>(-100);
        assert(runtime.integer_argument(index) == -7);
        assert(runtime.integer_argument_value(index, -100) == -7);
        record.payload[index] = bits(-100.0f);
        assert(runtime.float_argument(index) == -7.0f);
        assert(runtime.float_argument_value(index, -100.0f) == -7.0f);
        assert(runtime.stack.pointer == 800);
        record.payload[index] = bits(-0.5f);
        assert(runtime.float_argument(index) == 6.25f && variable == 0);
        assert(runtime.float_argument_value(index, -0.5f) == 6.25f && variable == 0);
        record.payload[index] = bits(-0.0f);
        runtime.stack.words[4] = bits(2.5f);
        assert(runtime.float_argument(index) == 2.5f);
        assert(runtime.float_argument_value(index, -0.0f) == 2.5f);

        record.payload[index] = static_cast<std::uint32_t>(-101);
        assert(runtime.integer_argument(index) == -321 && variable == -101);
        assert(runtime.consuming_integer(index) == -321 && variable == -101);
        assert(runtime.integer_argument_value(index, -101) == -321);
        assert(runtime.consuming_integer_value(index, -101) == -321);
        assert(runtime.integer_destination(index) == &integer_slot && variable == -101);
        record.payload[index] = bits(-101.75f);
        assert(runtime.float_argument(index) == 6.25f && variable == -101);
        assert(runtime.consuming_float(index) == 6.25f && variable == -101);
        assert(runtime.float_argument_value(index, -101.75f) == 6.25f);
        assert(runtime.consuming_float_value(index, -101.75f) == 6.25f);
        assert(runtime.float_destination(index) == &float_slot && variable == -101);
        assert(runtime.float_destination_at(&record.instruction, 32, index) == &float_slot);
        assert(integer_reads && float_reads && integer_writes && float_writes);
    }
}

int main() { check_stack(); check_runtime(); }
