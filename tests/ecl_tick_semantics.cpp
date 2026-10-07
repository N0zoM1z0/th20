#include "EclRuntime.hpp"

#include <array>
#include <bit>
#include <cassert>
#include <cmath>
#include <cstring>
#include <limits>
#include <vector>

namespace {
struct Record {
    th20::EclInstruction header{};
    std::array<std::uint32_t, 8> arguments{};
};
static_assert(sizeof(Record) == 48);
std::vector<Record> program;
std::array<std::int32_t, 8> integers{};
std::array<float, 8> floats{};
std::vector<int> reads;
int delegated_status;
int delegated_calls;
int spawn_id, spawn_skip, termination_calls;
th20::IntrusiveLink<th20::EclRuntime>* found_runtime;
int destination_frame, destination_index;

Record record(int opcode, int time = 0) {
    Record result;
    result.header.opcode = static_cast<std::int16_t>(opcode);
    result.header.time = time;
    result.header.length = sizeof(Record);
    result.header.rank = 15;
    return result;
}
std::uint32_t word(float value) { return std::bit_cast<std::uint32_t>(value); }
bool close(float value, float expected) { return std::fabs(value - expected) < 0.0001f; }
void load(th20::EclRuntime& runtime, std::initializer_list<Record> records) {
    program.assign(records);
    runtime.position.subroutine = 0;
    runtime.position.offset = 0;
    runtime.time = 0;
    runtime.rank = 15;
    runtime.stack.pointer = 0;
    runtime.stack.frame_base = 0;
    runtime.stack.words.clear();
    runtime.interpolators.clear();
    integers.fill(0);
    floats.fill(0);
    reads.clear();
    delegated_calls = 0;
}
std::int32_t pop_integer(th20::ScriptStack& stack) {
    std::int32_t result;
    stack.pop(4, &result, 'i');
    return result;
}
float pop_float(th20::ScriptStack& stack) {
    float result;
    stack.pop(4, &result, 'f');
    return result;
}
template<class T> void push(th20::ScriptStack& stack, T value, char tag) {
    stack.push(4, &value, tag);
}
}

// Explicit test-only dependencies. The accepted body runs on maintained owners
// and real math/interpolation implementations; these bounded VM fixtures do not
// claim native constructor, resolver, generic-copy or async lifetime fidelity.
namespace th20 {
EclScriptPosition::EclScriptPosition() : subroutine(-1), offset(-1) {}
EclRuntime::EclRuntime()
    : time(0), async_id(-1), manager(nullptr), signal(-1), rank(0), flags(0) {}
EclManager::EclManager()
    : field_04(0), field_08(0), current_runtime(&main), loader(nullptr) {}
EclManager::~EclManager() = default;
std::int32_t EclManager::execute_opcode() {
    ++delegated_calls;
    if (delegated_status == 1) current_runtime->time -= 10;
    return delegated_status;
}
std::int32_t EclManager::read_integer(std::int32_t index) { return integers.at(index); }
std::int32_t* EclManager::integer_destination(std::int32_t index) { return &integers.at(index); }
float EclManager::read_float(std::int32_t index) { return floats.at(index); }
float* EclManager::float_destination(std::int32_t index) { return &floats.at(index); }
int EclManager::spawn(std::int32_t id, std::int32_t skip) {
    spawn_id = id; spawn_skip = skip; return 0;
}
void EclManager::terminate_async() { ++termination_calls; }
IntrusiveLink<EclRuntime>* EclManager::find_runtime(std::int32_t) { return found_runtime; }
EclLoader::EclLoader() : file_count(0), subroutine_count(0), files{}, fields_10c{} {}
EclLoader::~EclLoader() = default;
std::int32_t EclLoader::callback_0(std::uint32_t) { return 0; }
std::int32_t EclLoader::callback_1(std::uint32_t) { return 0; }
EclInstruction* EclLoader::instruction(std::int32_t subroutine, std::int32_t offset) {
    assert(subroutine == 0 && offset >= 0 && offset % sizeof(Record) == 0);
    return &program.at(static_cast<unsigned>(offset) / sizeof(Record)).header;
}
EclInstruction* EclRuntime::current() {
    return manager->loader->instruction(position.subroutine, position.offset);
}
std::int32_t EclRuntime::integer_argument(std::int32_t index) {
    reads.push_back(index);
    auto* record = reinterpret_cast<Record*>(current());
    return std::bit_cast<std::int32_t>(record->arguments.at(index));
}
float EclRuntime::float_argument(std::int32_t index) {
    reads.push_back(index);
    auto* record = reinterpret_cast<Record*>(current());
    return std::bit_cast<float>(record->arguments.at(index));
}
std::int32_t EclRuntime::consuming_integer(std::int32_t index) { return integer_argument(index); }
float EclRuntime::consuming_float(std::int32_t index) { return float_argument(index); }
std::int32_t EclRuntime::consuming_integer_value(std::int32_t index, std::int32_t value) {
    reads.push_back(index); return value;
}
std::int32_t* EclRuntime::integer_destination(std::int32_t index) { return &integers.at(index); }
float* EclRuntime::float_destination(std::int32_t index) { return &floats.at(index); }
float* EclRuntime::float_destination_at(EclInstruction*, std::int32_t frame, std::int32_t index) {
    destination_frame = frame; destination_index = index; return &floats.at(index);
}
int EclRuntime::call_into(EclRuntime*, std::int32_t, std::int32_t) {
    // Invocation is exercised independently by ecl_call_semantics.cpp.
    return -1;
}
void EclScriptInterpolation::set_tangent_start(const float& value) { tangent_start = value; }
void EclScriptInterpolation::set_tangent_end(const float& value) { tangent_end = value; }
void EclScriptInterpolation::reset_time() { timer = 0; }
std::int32_t ScriptStack::pointer_value() const { return pointer; }
std::int32_t ScriptStack::frame_value() const { return frame_base; }
void ScriptStack::set_pointer(std::int32_t value) { pointer = value; }
int ScriptStack::enter_frame(std::int32_t bytes) {
    pointer += bytes;
    const int previous = frame_base;
    push(4, &previous, 0);
    frame_base = pointer;
    return 0;
}
int ScriptStack::push(std::int32_t bytes, const void* input, char tag) {
    assert(bytes == 4);
    if (tag) { absolute(pointer) = static_cast<unsigned char>(tag); pointer += 4; }
    std::memcpy(&absolute(pointer), input, 4);
    pointer += 4;
    return 0;
}
int ScriptStack::pop(std::int32_t bytes, void* output, char tag) {
    assert(bytes == 4 && pointer >= 4);
    pointer -= 4;
    std::memcpy(output, &absolute(pointer), 4);
    if (tag) { pointer -= 4; assert(absolute(pointer) == static_cast<unsigned char>(tag)); }
    return 0;
}
GameRandom script_random(0);
std::uint32_t GameRandom::next() { return 0; } // Only a deterministic dependency fixture.
}

int main() {
    th20::EclManager manager;
    th20::EclLoader loader;
    auto& runtime = manager.main;
    runtime.manager = &manager;
    manager.loader = &loader;
    const auto future = record(0, 100);

    load(runtime, {record(0), future});
    assert(runtime.tick(0.5f) == 0 && runtime.time == 0.5f && runtime.position.offset == 48);
    auto skipped = record(1); skipped.header.rank = 2; skipped.header.stack_drop = 8;
    load(runtime, {skipped, future}); runtime.rank = 1; runtime.stack.pointer = 8;
    assert(runtime.tick(1) == 0 && runtime.stack.pointer == 8 && runtime.position.offset == 48);
    load(runtime, {record(1)});
    assert(runtime.tick(1) == -1 && runtime.position.offset == -1 && runtime.position.subroutine == -1);
    runtime.position.offset = 48;
    assert(runtime.tick(1) == -1 && runtime.position.offset == 48);

    // Independent arithmetic answers, including operand order and signed division.
    for (auto [opcode, expected] : std::array<std::array<int, 2>, 5>{{
             {{50, -4}}, {{52, -10}}, {{54, -21}}, {{56, -2}}, {{58, -1}}}}) {
        load(runtime, {record(opcode), future});
        push(runtime.stack, -7, 'i'); push(runtime.stack, 3, 'i');
        program[0].header.stack_drop = 8;
        assert(runtime.tick(1) == 0 && program[0].header.stack_drop == 0);
        assert(pop_integer(runtime.stack) == expected && runtime.stack.pointer == 0);
    }
    for (auto [opcode, expected] : std::array<std::array<float, 2>, 4>{{
             {{51, 9}}, {{53, 5}}, {{55, 14}}, {{57, 3.5f}}}}) {
        load(runtime, {record(static_cast<int>(opcode)), future});
        push(runtime.stack, 7.0f, 'f'); push(runtime.stack, 2.0f, 'f');
        assert(runtime.tick(1) == 0 && pop_float(runtime.stack) == expected);
    }
    for (int opcode : {59, 61, 63, 65, 67, 69}) {
        load(runtime, {record(opcode), future});
        push(runtime.stack, -2, 'i'); push(runtime.stack, 3, 'i');
        assert(runtime.tick(1) == 0);
        const bool expected = opcode == 61 || opcode == 63 || opcode == 65;
        assert(pop_integer(runtime.stack) == expected);
    }
    for (int opcode : {60, 62, 64, 66, 68, 70}) {
        load(runtime, {record(opcode), future});
        push(runtime.stack, std::numeric_limits<float>::quiet_NaN(), 'f');
        push(runtime.stack, 1.0f, 'f');
        assert(runtime.tick(1) == 0 && pop_integer(runtime.stack) == (opcode == 62));
    }
    for (auto [opcode, expected] : std::array<std::array<int, 2>, 5>{{
             {{73, 1}}, {{74, 1}}, {{75, 6}}, {{76, 7}}, {{77, 1}}}}) {
        load(runtime, {record(opcode), future});
        push(runtime.stack, 5, 'i'); push(runtime.stack, 3, 'i');
        assert(runtime.tick(1) == 0 && pop_integer(runtime.stack) == expected);
    }
    load(runtime, {record(78), future}); program[0].arguments[0] = 9;
    assert(runtime.tick(1) == 0 && integers[0] == 8 && pop_integer(runtime.stack) == 9);

    // Native polar sequencing must read direction2 before length3.
    load(runtime, {record(81), future});
    program[0].arguments[2] = word(0.0f); program[0].arguments[3] = word(4.0f);
    assert(runtime.tick(1) == 0 && floats[0] == 4 && floats[1] == 0);
    assert((reads == std::vector<int>{2, 3}));
    load(runtime, {record(87), future});
    for (int i = 1; i != 5; ++i) program[0].arguments[i] = word(float(i));
    assert(runtime.tick(1) == 0 && close(floats[0], 0.7853982f));
    assert((reads == std::vector<int>{1, 2, 3, 4}));
    load(runtime, {record(88), future}); push(runtime.stack, 9.0f, 'f');
    assert(runtime.tick(1) == 0 && pop_float(runtime.stack) == 3);

    // Relative jump changes both instruction and time; branch truth decides
    // whether the intervening end instruction executes.
    for (int opcode : {12, 13, 14}) {
        load(runtime, {record(opcode), record(1), future});
        program[0].arguments[0] = 96; program[0].arguments[1] = 7;
        if (opcode != 12) push(runtime.stack, opcode == 13 ? 0 : 1, 'i');
        assert(runtime.tick(0.5f) == 0 && runtime.position.offset == 96 && runtime.time == 7.5f);
    }
    for (int status : {-1, 0, 1, 2}) {
        load(runtime, {record(300), future});
        runtime.stack.pointer = 8; program[0].header.stack_drop = 4;
        delegated_status = status;
        assert(runtime.tick(1) == 0 && delegated_calls == 1);
        if (status == -1) assert(runtime.time == 0 && runtime.position.offset == 0 && runtime.stack.pointer == 8);
        if (status == 1) assert(runtime.time == -9 && runtime.position.offset == 0 && runtime.stack.pointer == 8);
        if (status == 0 || status == 2) assert(runtime.time == 1 && runtime.position.offset == 48 && runtime.stack.pointer == 4);
    }

    load(runtime, {record(15), future});
    assert(runtime.tick(1) == 0 && spawn_id == -1 && spawn_skip == 0);
    th20::EclRuntime child;
    th20::IntrusiveLink<th20::EclRuntime> link(&child);
    found_runtime = &link;
    load(runtime, {record(18), record(20), record(19), record(17), future});
    program[1].arguments[1] = 42;
    assert(runtime.tick(1) == 0 && child.flags == 0 && child.signal == 42 && child.position.offset == -1);

    // Exercise real scalar interpolation sampling through the tick tail and
    // recovery of saved instruction/frame address, not a fake sample result.
    load(runtime, {future});
    runtime.interpolators.resize(1);
    auto& interpolation = runtime.interpolators[0];
    interpolation.position.subroutine = 0; interpolation.position.offset = 0;
    interpolation.frame_base = 64;
    interpolation.start = 2; interpolation.end = 10;
    interpolation.duration = 4; interpolation.mode = 0;
    assert(runtime.tick(1) == 0 && floats[1] == 4);
    assert(destination_frame == 64 && destination_index == 1);
    assert(interpolation.timer.current == 1);
    runtime.interpolators.clear();

    th20::script_random.modulus = 100;
    assert(th20::script_random.radians() == -3.1415927410125732f);
}
