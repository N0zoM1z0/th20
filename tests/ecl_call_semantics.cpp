#include "EclRuntime.hpp"

#include <array>
#include <bit>
#include <cassert>
#include <cstring>
#include <string>
#include <vector>

namespace {
alignas(th20::EclInstruction) std::array<std::uint32_t, 64> instruction_storage{};
th20::EclInstruction* instruction;
std::vector<int> reads;
bool activation_failure;
bool consume_stack;
th20::EclRuntime* activated;
std::string activated_name;

void prepare(int skip, int name_skip) {
    instruction_storage.fill(0);
    instruction = ::new (instruction_storage.data()) th20::EclInstruction{};
    instruction->argument_count = static_cast<std::uint8_t>(skip + 5);
    auto* payload = reinterpret_cast<unsigned char*>(instruction + 1);
    const int descriptor_base = 32;
    std::memcpy(payload, &descriptor_base, 4);
    std::memcpy(payload + name_skip * 4 + 4, "callee", 7);
    const std::array<char, 4> from{'f', 'g', 'i', 'i'};
    const std::array<char, 4> to{'f', 'i', 'f', 'i'};
    const std::array<std::uint32_t, 4> values{
        std::bit_cast<std::uint32_t>(1.25f), std::bit_cast<std::uint32_t>(-3.75f),
        static_cast<std::uint32_t>(-7), 19};
    for (int i = 0; i != 4; ++i) {
        auto* descriptor = payload + descriptor_base + skip * 4 + 4 + i * 8;
        descriptor[0] = from[i];
        descriptor[1] = to[i];
        std::memcpy(descriptor + 4, &values[i], 4);
    }
    reads.clear();
    activated = nullptr;
    activated_name.clear();
    activation_failure = false;
    consume_stack = false;
}

void check_arguments(const th20::ScriptStack& stack, std::size_t first) {
    assert(stack.words[first] == std::bit_cast<std::uint32_t>(1.25f));
    assert(stack.words[first + 1] == static_cast<std::uint32_t>(-3));
    assert(stack.words[first + 2] == std::bit_cast<std::uint32_t>(-7.0f));
    assert(stack.words[first + 3] == 19);
}
}

// Test-only dependency fixtures: production constructors,
// argument resolution and loader activation are not accepted by this test.
// The fixture uses the maintained owners and bounds calls to four-byte words.
namespace th20 {
EclScriptPosition::EclScriptPosition() : subroutine(-1), offset(-1) {}
EclRuntime::EclRuntime()
    : time(0), async_id(-1), manager(nullptr), signal(-1), rank(0), flags{} {}
EclManager::EclManager()
    : field_04(0), field_08(0), current_runtime(&main), loader(nullptr) {}
EclManager::~EclManager() = default;
std::int32_t EclManager::execute_opcode() { return 0; }
std::int32_t EclManager::read_integer(std::int32_t) { return 0; }
std::int32_t* EclManager::integer_destination(std::int32_t) { return nullptr; }
float EclManager::read_float(std::int32_t) { return 0; }
float* EclManager::float_destination(std::int32_t) { return nullptr; }
EclLoader* EclManager::loader_value() const { return loader; }
int EclLoader::activate(EclManager* manager, const char* name) {
    activated = manager->current_runtime;
    activated_name = name;
    activated->position = EclScriptPosition{};
    activated->position.subroutine = activation_failure ? -1 : 12;
    activated->position.offset = 0;
    activated->time = 0;
    return activation_failure ? 1 : 0;
}
EclInstruction* EclRuntime::current() { return instruction; }
float EclRuntime::consuming_float_value(std::int32_t index, float value) {
    reads.push_back(index);
    if (consume_stack && reads.size() == 1) stack.pointer -= 8;
    return value;
}
std::int32_t EclRuntime::consuming_integer_value(std::int32_t index, std::int32_t value) {
    reads.push_back(index);
    return value;
}
std::int32_t ScriptStack::pointer_value() const { return pointer; }
void ScriptStack::set_pointer(std::int32_t value) { pointer = value; }
}

int main() {
    th20::EclManager manager;
    th20::EclLoader loader;
    th20::EclRuntime caller, target, saved;
    manager.loader = &loader;
    manager.current_runtime = &saved;
    caller.manager = &manager;
    target.manager = &manager;
    caller.time = 6.5f;
    caller.position.subroutine = 8;
    caller.position.offset = 100;

    prepare(0, 0);
    target.stack.words.assign(16, 0xa5a5a5a5);
    assert(caller.call_into(&target, 0, 0) == 0);
    assert((reads == std::vector<int>{1, 2, 3, 4}));
    assert(activated == &target && activated_name == "callee");
    assert(manager.current_runtime == &saved);
    assert(target.stack.pointer == 20 && target.stack.words[0] == 0);
    assert(target.stack.words[1] == 4);
    for (int i = 2; i != 5; ++i) assert(target.stack.words[i] == 0xffffffff);
    check_arguments(target.stack, 5);
    assert(target.stack.words[9] == 0xa5a5a5a5);
    assert(caller.time == 6.5f && caller.position.offset == 100);

    // Same-runtime nested call captures the post-consumption pointer, copies the
    // previous frame word back at the original boundary and saves caller fields
    // before activation changes them.
    prepare(2, 3);
    consume_stack = true;
    caller.stack.words.assign(24, 0xa5a5a5a5);
    caller.stack.pointer = 32;
    caller.stack.words[5] = 0x44;
    assert(caller.call_into(&caller, 2, 3) == 0);
    assert((reads == std::vector<int>{3, 4, 5, 6}));
    assert(activated == &caller && activated_name == "callee");
    assert(manager.current_runtime == &saved);
    assert(caller.stack.pointer == 48);
    assert(caller.stack.words[7] == 0x44);
    assert(caller.stack.words[8] == 24);
    assert(caller.stack.words[9] == std::bit_cast<std::uint32_t>(6.5f));
    assert(caller.stack.words[10] == 100 && caller.stack.words[11] == 8);
    check_arguments(caller.stack, 12);
    assert(caller.stack.words[0] == 0xa5a5a5a5);
    assert(caller.stack.words[16] == 0xa5a5a5a5);

    prepare(0, 0);
    activation_failure = true;
    target.stack.pointer = 0;
    assert(caller.call_into(&target, 0, 0) == -1);
    assert(manager.current_runtime == &target);
    assert(caller.position.subroutine == -1 && caller.position.offset == -1);
    assert(target.position.subroutine == -1 && target.position.offset == 0);
    assert(target.stack.pointer == 20);
}
